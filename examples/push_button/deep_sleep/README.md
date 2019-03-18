# Example: deep sleep

(See the README.md file on MQTT and Push_button in the 'examples' directory for more information about using MQTT.)
This example illustrates usage of deep sleep mode and External push button as wakeup source.

The following wake up source is configured:
- EXT1:  wake up the chip if any of the two buttons are pressed (GPIO25)


## How to use example

### Hardware Required

This example can be executed on any ESP32 board, the only required interface is WiFi and connection to internet.
The Push_Button should be atached to PIN 25.

### Configure the project

```
make menuconfig
```

* Set serial port under Serial Flasher Options.

* Set ssid and password for the board to connect to AP.


### Building and Running

Build the project and flash it to the board.
The board will go into deep sleep mode. When you presse the push_buton, the board will wake up connect to the wifi, send a MQQT message and go to sleep mode again.

## Example Output

Entering deep sleep
ets Jun  8 2016 00:22:57

rst:0x5 (DEEPSLEEP_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0xee
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:DIO, clock div:2
load:0x3fff0018,len:4
load:0x3fff001c,len:6340
load:0x40078000,len:11308
load:0x40080400,len:6672
entry 0x40080764
I (29) boot: ESP-IDF v3.3-beta1-430-g7cdd19fb6-dirty 2nd stage bootloader
I (29) boot: compile time 15:31:45
I (31) boot: Enabling RNG early entropy source...
I (36) boot: SPI Speed      : 40MHz
I (40) boot: SPI Mode       : DIO
I (44) boot: SPI Flash Size : 4MB
I (48) boot: Partition Table:
I (52) boot: ## Label            Usage          Type ST Offset   Length
I (59) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (67) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (74) boot:  2 factory          factory app      00 00 00010000 00100000
I (82) boot: End of partition table
I (86) esp_image: segment 0: paddr=0x00010020 vaddr=0x3f400020 size=0x1f440 (128064) map
I (139) esp_image: segment 1: paddr=0x0002f468 vaddr=0x3ffb0000 size=0x00ba8 (  2984) load
I (141) esp_image: segment 2: paddr=0x00030018 vaddr=0x400d0018 size=0x88bfc (560124) map
I (342) esp_image: segment 3: paddr=0x000b8c1c vaddr=0x3ffb0ba8 size=0x024bc (  9404) load
I (346) esp_image: segment 4: paddr=0x000bb0e0 vaddr=0x40080000 size=0x00400 (  1024) load
I (349) esp_image: segment 5: paddr=0x000bb4e8 vaddr=0x40080400 size=0x10be8 ( 68584) load
I (386) esp_image: segment 6: paddr=0x000cc0d8 vaddr=0x400c0000 size=0x00064 (   100)
I (387) esp_image: segment 7: paddr=0x000cc144 vaddr=0x50000200 size=0x00008 (     8)
I (403) boot: Loaded app from partition at offset 0x10000
I (403) boot: Disabling RNG early entropy source...
I (404) cpu_start: Pro cpu up.
I (408) cpu_start: Application information:
I (413) cpu_start: Project name:     deep_sleep
I (418) cpu_start: App version:      v3.3-beta1-430-g7cdd19fb6-dirty
I (425) cpu_start: Compile time:     15:31:48
I (430) cpu_start: Compile date:     Mar 14 2019
I (435) cpu_start: ESP-IDF:          v3.3-beta1-430-g7cdd19fb6-dirty
I (442) cpu_start: Starting app cpu, entry point is 0x4008129c
I (0) cpu_start: App cpu up.
I (453) heap_init: Initializing. RAM available for dynamic allocation:
I (460) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (466) heap_init: At 3FFB9260 len 00026DA0 (155 KiB): DRAM
I (472) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (478) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (485) heap_init: At 40090FE8 len 0000F018 (60 KiB): IRAM
I (491) cpu_start: Pro cpu start user code
I (509) cpu_start: Starting scheduler on PRO CPU.
I (0) cpu_start: Starting scheduler on APP CPU.
Wake up from GPIO
Enabling EXT1 wakeup on pins GPIO25
I (2618) wifi: wifi driver task: 3ffc0b04, prio:23, stack:3584, core=0
I (2618) wifi: wifi firmware version: 66a98c0
I (2618) wifi: config NVS flash: enabled
I (2628) wifi: config nano formating: disabled
I (2628) system_api: Base MAC address is not set, read default base MAC address from BLK0 of EFE
I (2638) system_api: Base MAC address is not set, read default base MAC address from BLK0 of EFE
I (2688) wifi: Init dynamic tx buffer num: 32
I (2688) wifi: Init data frame dynamic rx buffer num: 32
I (2688) wifi: Init management frame dynamic rx buffer num: 32
I (2688) wifi: Init static rx buffer size: 1600
I (2698) wifi: Init static rx buffer num: 10
I (2698) wifi: Init dynamic rx buffer num: 32
I (2708) MQTT_EXAMPLE: start the WIFI SSID:[Wifi Wiifor]
I (2728) phy: phy_version: 4100, 6fa5e27, Jan 25 2019, 17:02:06, 0, 1
I (2738) wifi: mode : sta (30:ae:a4:f1:e0:b0)
I (2738) MQTT_EXAMPLE: Waiting for wifi
I (3948) wifi: new:<11,0>, old:<1,0>, ap:<255,255>, sta:<11,0>, prof:1
I (5908) wifi: state: init -> auth (b0)
I (5968) wifi: state: auth -> assoc (0)
I (5978) wifi: state: assoc -> run (10)
I (5998) wifi: connected with Wifi Wiifor, channel 11, bssid = b8:69:f4:03:44:8e
I (5998) wifi: pm start, type: 1

I (6618) event: sta ip: 192.168.1.194, mask: 255.255.255.0, gw: 192.168.1.254
I (6618) system_api: Base MAC address is not set, read default base MAC address from BLK0 of EFE
I (6628) MQTT_EXAMPLE: MQTT_EVENT_BEFORE_CONNECT
I (7138) MQTT_CLIENT: Sending MQTT CONNECT message, type: 1, id: 0000
I (7288) MQTT_EXAMPLE: MQTT_EVENT_CONNECTED
Wifi started
MQTT started
COUNT : 1
I (7628) MQTT_EXAMPLE: sent publish successful, msg={"count": "1"}
message sent
I (7628) wifi: state: run -> init (0)
I (7628) wifi: pm stop, total sleep time: 1072902 us / 1630137 us

I (7638) wifi: new:<11,0>, old:<11,0>, ap:<255,255>, sta:<11,0>, prof:1
E (7648) MQTT_CLIENT: Read error or end of stream
I (7648) MQTT_EXAMPLE: MQTT_EVENT_DISCONNECTED
I (7658) wifi: flush txq
I (7658) wifi: stop sw txq
I (7658) wifi: lmac stop hw txq
E (7658) wifi: esp_wifi_connect 956 wifi not start
Entering deep sleep


# Note

In this example, we don't disable BT using the apprpriate calls (esp_bluedroid_disable(), esp_bt_controller_disable()). However, WiFi and BT connections will not be maintained in deep sleep or light sleep, even if these functions are not called.
