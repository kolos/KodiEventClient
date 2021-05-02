# ESP8266 Kodi EventClient
A simple EventClient for remote controlling Kodi from the ESP8266

## Example

```
#include <KodiEventClient.h>

KodiEventClient kodiClient("192.168.0.4", 9777);
/* ... */
kodiClient.sendButton("play_pause");
```

Check [List of keynames | Kodi.wiki](https://kodi.wiki/view/List_of_keynames "List of keynames | Kodi.wiki") for other keynames.

## Kodi settings

Enable: **Allow remote control from application on other systems**:
![Settings page](screenshots/allow_kodi_remote_control.png "Settings page")

## Other client implementations
* https://github.com/xbmc/xbmc/tree/master/tools/EventClients
