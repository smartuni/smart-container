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

### Communication

- UART serial via TX/RX pins on top or bottom (Baudrate: default 9600, can be changed if desired)

### GPS Breakouts

- GPS Reset (input): manually reset the GPS module
- FIX (output): works like the "Red LED" to indicate if satellites are found
- PPS (output): "pulse per second"
- EN (input): Pulling it high disables the GPS module
