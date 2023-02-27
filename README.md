# ESP32C3_TTL_TCP_Bridge
Bridge TTL to both TCP and the USB port of a Xiao ESP32C3

I was running short on "classic" TTL to USB adapters (like ch340 or ftdi),
but had a couple of spare [ESP32C3](https://www.seeedstudio.com/Seeed-XIAO-ESP32C3-p-5431.html) around.

Started with just bridging between usb and uart, but enhanced to bridge to wifi as well.

Connecting from a linux host to the tcp port is as simple as
```
socat pty,link=$HOME/ttyV0,raw,waitslave tcp:YOUR-ESP-IP:8880 & sleep 3 && minicom -D $HOME/ttyV0 --color=on -b115200
```

enjoy at your own risk.
