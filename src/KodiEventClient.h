#ifndef KODIEVENTCLIENT_H
#define KODIEVENTCLIENT_H

#include <Arduino.h>
#include <WiFiUdp.h>

#define MS_ABSOLUTE    0x01
//#define MS_RELATIVE    0x02

#define BTN_USE_NAME   0x01
#define BTN_DOWN       0x02
#define BTN_UP         0x04
#define BTN_USE_AMOUNT 0x08
#define BTN_QUEUE      0x10
#define BTN_NO_REPEAT  0x20
#define BTN_VKEY       0x40
#define BTN_AXIS       0x80

#define PT_HELO         0x01
#define PT_BYE          0x02
#define PT_BUTTON       0x03
#define PT_MOUSE        0x04
#define PT_PING         0x05
#define PT_BROADCAST    0x06
#define PT_NOTIFICATION 0x07
#define PT_BLOB         0x08
#define PT_LOG          0x09
#define PT_ACTION       0x0A
#define PT_DEBUG        0xFF

#define ICON_NONE       0x00
#define ICON_JPEG       0x01
#define ICON_PNG        0x02
#define ICON_GIF        0x03

#define MAX_PACKET_SIZE  1024
#define HEADER_SIZE      32
#define MAX_PAYLOAD_SIZE (MAX_PACKET_SIZE - HEADER_SIZE)

#define MAJOR_VERSION 2
#define MINOR_VERSION 0

#define LOGDEBUG   0
#define LOGINFO    1
#define LOGNOTICE  2
#define LOGWARNING 3
#define LOGERROR   4
#define LOGSEVERE  5
#define LOGFATAL   6
#define LOGNONE    7

#define ACTION_EXECBUILTIN 0x01
#define ACTION_BUTTON      0x02

namespace KodiEventClientLib {

class KodiEventClient
{
  private:
    const char* host;
    const uint16_t port;
    uint16_t fillZero(char* buf, uint8_t len);
    uint16_t fillChar(char* buf, uint8_t val);
    uint16_t fillShort(char* buf, uint16_t val);
    uint16_t fillLong(char* buf, uint32_t val);
    uint16_t fillString(char* buf, const char* val);
    uint16_t fillHeader(char* buff, uint16_t payloadType, uint16_t payloadSize);
    void sendUdpPacket(const char* packet, uint16_t packetSize);
  public:
    KodiEventClient(const char* host, uint16_t port);
    void sendButton(const char* kodiKeyName);
    void sendAction(const char* actionName);
};

} // End Of namespace KodiEventClientLib

typedef KodiEventClientLib::KodiEventClient KodiEventClient;

#endif