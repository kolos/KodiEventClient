#include "KodiEventClient.h"

using namespace KodiEventClientLib;

KodiEventClient::KodiEventClient(const char* host, uint16_t port):
  host(host)
  , port(port)
{
  //
}

void KodiEventClient::sendUdpPacket(const char* packet, uint16_t packetSize)
{
    WiFiUDP udp;
    udp.beginPacket(host, port);
    udp.write(packet, packetSize);
    udp.endPacket();
}

uint16_t KodiEventClient::fillZero(char* buf, uint8_t len)
{
    memset(buf, 0, len);
    return len;
}

uint16_t KodiEventClient::fillString(char* buf, const char* val)
{
    uint16_t str_len = strlen(val);
    strcpy(buf, val);
    buf[str_len] = 0;
    return str_len + 1;
}

uint16_t KodiEventClient::fillChar(char* buf, uint8_t val)
{
    buf[0] = val;
    return 1;
}

uint16_t KodiEventClient::fillShort(char* buf, uint16_t val)
{
    buf[0] = (val >> (1 * 8)) & 0xFF;
    buf[1] = (val >> (0 * 8)) & 0xFF;
    
    return 2;
}

uint16_t KodiEventClient::fillLong(char* buf, uint32_t val)
{
    buf[0] = (val >> (3 * 8)) & 0xFF;
    buf[1] = (val >> (2 * 8)) & 0xFF;
    buf[2] = (val >> (1 * 8)) & 0xFF;
    buf[3] = (val >> (0 * 8)) & 0xFF;
    
    return 4;
}

uint16_t KodiEventClient::fillHeader(char* buf, uint16_t payloadType, uint16_t payloadSize)
{
    uint16_t i = 0;

    // Signature
    i += fillLong(buf + i, 0x58424D43); // 'XBMC'

    // Version
    i += fillChar(buf + i, MAJOR_VERSION);
    i += fillChar(buf + i, MINOR_VERSION);

    // PacketType
    i += fillShort(buf + i, payloadType);

    // Sequence number
    i += fillLong(buf + i, 1);

    // No. of packets in msg
    i += fillLong(buf + i, 1);

    // Payload size
    i += fillShort(buf + i, payloadSize);

    // Client's unique token
    i += fillLong(buf + i, 0x45535000); // 'ESP'

    // Reserved
    i += fillZero(buf + i, 10);
    
    return HEADER_SIZE;
}

void KodiEventClient::sendButton(const char* kodiKeyName)
{
    uint16_t data_len = strlen(kodiKeyName) + /*strlen("KB")*/ 2 + 8;
    char packet[HEADER_SIZE + data_len];

    fillHeader(packet, PT_BUTTON, data_len);

    uint16_t i = HEADER_SIZE;
    // ButtonCode
    i += fillShort(packet + i, 0);

    // Flags
    i += fillShort(packet + i, BTN_NO_REPEAT | BTN_USE_NAME | BTN_DOWN);

    // Amount
    i += fillShort(packet + i, 0);

    // DeviceMap
    i += fillString(packet + i, "KB");
    
    // ButtonName
    i += fillString(packet + i, kodiKeyName);

    sendUdpPacket(packet, sizeof(packet));
}

void KodiEventClient::sendAction(const char* actionName)
{
    uint16_t data_len = 1 + strlen(actionName) + 1;
    char packet[HEADER_SIZE + data_len];

    fillHeader(packet, PT_ACTION, data_len);

    uint16_t i = HEADER_SIZE;
    // ActionType
    i += fillChar(packet + i, ACTION_EXECBUILTIN);

    // ActionName
    i += fillString(packet + i, actionName);

    sendUdpPacket(packet, sizeof(packet));
}