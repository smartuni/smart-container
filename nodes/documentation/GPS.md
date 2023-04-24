# GPS Sensor

## Board Information

### General Information

- Sensor Type: GPS
- Board: Adafruit Ultimate GPS Featherwing
- The board is built around the MTK3339 GPS module

**Links**

- [Documentation](https://learn.adafruit.com/adafruit-ultimate-gps-featherwing)

### Main Features

- Can track up to 22 satellites on 66 channels
- High-sensitivity receiver (-165 dB tracking)
- Built-in antenna
- External antenna functionality
- can do up to 10 location updates a second for high speed, high sensitivity logging or tracking
- Power usage: 20 mA during navigation
- ENABLE pin to turn off the module for low-poser use
- CR1220 battery holder to keep the RTC running and allow warm starts
- Red LED: blinks at about 1Hz while searching for satellites and blinks once every 15 seconds when a fix is found to conserve power

### Electrical specifications

- +3.3V is needed for power supply (directly via 3V/GND pins, battery or USB)
- Power Consumption: 20 mA (Tracking), 25 mA (Acquisition)
- Backup Power Consumption (Coin cell): 7 µA

### Communication

- UART serial via TX/RX pins on top or bottom (Baudrate: default 9600, can be changed if desired)

### GPS Breakouts

- GPS Reset (input): manually reset the GPS module
- FIX (output): works like the "Red LED" to indicate if satellites are found
- PPS (output): "pulse per second"
- EN (input): Pulling it high disables the GPS module

## Integration

The sensor will be integrated into the project as follows:

- Power connection: 3V and GND pins
- UART connection at RX/TX pins. Baudrate may be configured through software.
- Reset GPS module by pulling '_GPS Reset_' pin to low
- Indicate GPS status by connecting LED to the '_FIX_' pin
- Sync. microcontroller to module by using the '_PPS_' (pulse per second) output
- Disable power to the GPS module (activate ultra-low-power mode) by pulling the '_EN_' pin high
- Insert CR1220 battery for keeping the RTC running and allowing warm starts
- Reset the microcontroller by pulling the RESET pin to GND (or manually by pressing the '_Reset_' button on the board)
- Optionally: Connect external GPS antenna into _uFL_ connector

### Software Requirements

- Wait for startup (approx. 34 seconds)
- Configure baudrate
- Wait until min. 1 fix was found and location is available
- Update position every x seconds (Update rate of GPS module: 1-10 Hz)
- Communicate with module using UART (via [RIOT UART module '_periph/uart.h_'](https://doc.riot-os.org/group__drivers__periph__uart.html))
- Concentrator observes the sensor - When update is available (status, location), it will be sent via CoAP
- If location has not changed for > x minutes, module will be set to "sleep mode" (disable GPS module)

### Code Examples

- [GPS Minimal](https://github.com/smartuni/AIT-SS2021/tree/98d020a79ef4a1cd3357b2acf7c9e30ed5663557/GPS_Minimal)
