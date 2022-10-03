## Components Used

- ESP8266 NodeMCU v3 board
- ILI9341 2.4" Monitor
- 3v relay

## Assemble

1. Connect the board to monitor using these pins

| Monitor Pin | Board Pin |
| ----------- | --------- |
| VCC         | 3V3       |
| GND         | GND       |
| CS          | D2        |
| RST         | D3        |
| DC          | D4        |
| SDI(MOSI)   | D7        |
| SCK         | D5        |
| LED         | 3V3       |

2. connect output pin to whatever you want
   D1 (GPIO5) : Ticking Number

3. setup arduino

- Go to `Preferences` tab and change the following:
  - add `http://arduino.esp8266.com/stable/package_esp8266com_index.json` to Additional Board Manager url
- Go to `tools` tab
  - change the `board` to `NodeMCU 1.0 (ESP-12E)`
  - change `upload speed` to `115200`
  - change `PORT` to match your port
    - more information [here](https://www.mathworks.com/help/supportpkg/arduinoio/ug/find-arduino-port-on-windows-mac-and-linux.html)
- Install these library
  - Adafruit ILI9341
  - Adafruit GFX Library
  - PubSubClient
  - RingBuf (refer to FAQ)
  - TaskScheduler

4. modify `env.h_example` to match your environment and rename it to `env.h`
5. verify and upload `main` project

### FAQ

##### Cannot compile RingBuf:

go to RingBuf.h and change the quote character to `"`
