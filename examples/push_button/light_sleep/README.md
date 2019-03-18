# Light Sleep Example

(See the README.md file in the upper level 'examples' directory for more information about examples.)

This example illustrates usage of light sleep mode. Unlike deep sleep mode, light sleep preserves the state of the memory, CPU, and peripherals. Execution of code on both CPUs is stopped when `esp_light_sleep_start` function is called. When the chip exits light sleep mode, execution continues at the point where it was stopped, and `esp_light_sleep_start` function returns.

The example enables the following wakeup sources:


- EXT0: wake up the chip if a button attached to GPIO25 is pressed (i.e. if GPIO25 goes low)

The example also prints time spent in light sleep mode to illustrate that timekeeping continues while the chip is in light sleep.



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
The board will go into light sleep mode. When you presse the push_buton, the board will wake up connect to the wifi, send a MQQT message and go to sleep mode again.

## Example Output

```
Entering light sleep
Returned from light sleep, reason: pin, t=70089 ms, slept for 65982 ms
Waiting for GPIO25 to go high...
I (4621) wifi: mode : sta (30:ae:a4:f1:e0:b0)
I (4741) wifi: new:<11,0>, old:<1,0>, ap:<255,255>, sta:<11,0>, prof:1
I (4751) wifi: state: init -> auth (b0)
I (4751) wifi: state: auth -> assoc (0)
I (4761) wifi: state: assoc -> run (10)
I (4791) wifi: connected with Wifi Wiifor, channel 11, bssid = b8:69:f4:03:44:8e
I (4791) wifi: pm start, type: 1

I (5561) event: sta ip: 192.168.1.194, mask: 255.255.255.0, gw: 192.168.1.254
I (6621) system_api: Base MAC address is not set, read default base MAC address from BLK0 of EFE
I (6621) MQTT_EXAMPLE: MQTT_EVENT_BEFORE_CONNECT
I (6681) MQTT_CLIENT: Sending MQTT CONNECT message, type: 1, id: 0000
I (7041) MQTT_EXAMPLE: MQTT_EVENT_CONNECTED
Wifi started
MQTT started
COUNT : 1
I (8621) MQTT_EXAMPLE: sent publish successful, msg={"count": "1"}
message sent
I (8621) wifi: state: run -> init (0)
I (8631) wifi: pm stop, total sleep time: 3027980 us / 3837121 us

I (8631) wifi: new:<11,0>, old:<11,0>, ap:<255,255>, sta:<11,0>, prof:1
E (8641) MQTT_CLIENT: Read error or end of stream
I (8641) MQTT_EXAMPLE: MQTT_EVENT_DISCONNECTED
I (8651) wifi: flush txq
I (8651) wifi: stop sw txq
I (8651) wifi: lmac stop hw txq
E (8651) wifi: esp_wifi_connect 956 wifi not start
Entering light sleep

```

In the scenario above, the button attached to GPIO13 was pressed once.



