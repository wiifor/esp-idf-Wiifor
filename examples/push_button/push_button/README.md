# Push_button  sample application
(See the README.md file on MQTT in the 'examples' directory for more information about using MQTT.)

This example connects to the broker URI selected using `make menuconfig` (using mqtt tcp transport)  and as a demonstration subscribes/unsubscribes and send a message on certain topic each time you press on the push_button. When the counter hits 10,  the LED lights up and the counter restarts from 0.

Note: If the URI equals `FROM_STDIN` then the broker address is read from stdin upon application startup (used for testing)

It uses ESP-MQTT library which implements mqtt client to connect to mqtt broker.

## How to use example

### Hardware Required

This example can be executed on any ESP32 board, the only required interface is WiFi and connection to internet.
The Push_Button should be atached to PIN 25 and the LED shouls be connected to PIN 26.

### Configure the project

```
make menuconfig
```

* Set serial port under Serial Flasher Options.

* Set ssid and password for the board to connect to AP.

### Build and Flash

Build the project and flash it to the board, then run monitor tool to view serial output:

```
make -j4 flash monitor
```

(To exit the serial monitor, type ``Ctrl-]``.)

See the Getting Started Guide for full steps to configure and use ESP-IDF to build projects.

## Example Output

````
I (396) boot: Loaded app from partition at offset 0x10000
I (396) boot: Disabling RNG early entropy source...
I (396) cpu_start: Pro cpu up.
I (400) cpu_start: Application information:
I (405) cpu_start: Project name:     ds18b20_onewire
I (410) cpu_start: App version:      v3.3-beta1-430-g7cdd19fb6-dirty
I (417) cpu_start: Compile time:     13:18:25
I (422) cpu_start: Compile date:     Mar 14 2019
I (428) cpu_start: ESP-IDF:          v3.3-beta1-430-g7cdd19fb6-dirty
I (435) cpu_start: Starting app cpu, entry point is 0x400811c4
I (0) cpu_start: App cpu up.
I (445) heap_init: Initializing. RAM available for dynamic allocation:
I (452) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (458) heap_init: At 3FFB9238 len 00026DC8 (155 KiB): DRAM
I (464) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (470) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (477) heap_init: At 40090510 len 0000FAF0 (62 KiB): IRAM
I (483) cpu_start: Pro cpu start user code
I (166) cpu_start: Starting scheduler on PRO CPU.
I (0) cpu_start: Starting scheduler on APP CPU.
I (167) gpio: GPIO[26]| InputEn: 0| OutputEn: 1| OpenDrain: 0| Pullup: 0| Pulldown: 0| Intr:0
I (167) gpio: GPIO[25]| InputEn: 1| OutputEn: 0| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:1
I (177) MQTT_EXAMPLE: [APP] Startup..
I (187) MQTT_EXAMPLE: [APP] Free memory: 270088 bytes
I (187) MQTT_EXAMPLE: [APP] IDF version: v3.3-beta1-430-g7cdd19fb6-dirty
I (227) wifi: wifi driver task: 3ffc1a5c, prio:23, stack:3584, core=0
I (227) wifi: wifi firmware version: 66a98c0
I (227) wifi: config NVS flash: enabled
I (237) wifi: config nano formating: disabled
I (237) system_api: Base MAC address is not set, read default base MAC address from BLK0 of EFUE
I (247) system_api: Base MAC address is not set, read default base MAC address from BLK0 of EFUE
I (277) wifi: Init dynamic tx buffer num: 32
I (277) wifi: Init data frame dynamic rx buffer num: 32
I (277) wifi: Init management frame dynamic rx buffer num: 32
I (277) wifi: Init static rx buffer size: 1600
I (287) wifi: Init static rx buffer num: 10
I (287) wifi: Init dynamic rx buffer num: 32
I (297) MQTT_EXAMPLE: start the WIFI SSID:[Wifi Wiifor]
I (407) phy: phy_version: 4100, 6fa5e27, Jan 25 2019, 17:02:06, 0, 0
I (407) wifi: mode : sta (30:ae:a4:f1:e0:b0)
I (407) MQTT_EXAMPLE: Waiting for wifi
I (1617) wifi: new:<11,0>, old:<1,0>, ap:<255,255>, sta:<11,0>, prof:1
I (2607) wifi: state: init -> auth (b0)
I (2607) wifi: state: auth -> assoc (0)
I (2617) wifi: state: assoc -> run (10)
I (2637) wifi: connected with Wifi Wiifor, channel 11, bssid = b8:69:f4:03:44:8e
I (2637) wifi: pm start, type: 1

I (3227) event: sta ip: 192.168.1.194, mask: 255.255.255.0, gw: 192.168.1.254
I (3227) system_api: Base MAC address is not set, read default base MAC address from BLK0 of EFE
I (3237) MQTT_EXAMPLE: MQTT_EVENT_BEFORE_CONNECT
I (3277) MQTT_CLIENT: Sending MQTT CONNECT message, type: 1, id: 0000
I (6147) MQTT_EXAMPLE: MQTT_EVENT_CONNECTED
cnt: 1
I (24267) MQTT_EXAMPLE: sent publish successful, msg={"count": "1"}
cnt: 2
I (35037) MQTT_EXAMPLE: sent publish successful, msg={"count": "2"}
````
