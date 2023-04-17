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

## Hardware connection
The module must be connected to the **Nucleo F103RB** board as follows:
- 3V -> CN6 3V3
- GND -> CN6 GND
- TX -> TODO
- RX -> TODO

## Usage
The module communicates via its UART interface. Therefore a board with U(S)ART capabilities is necessary to communicate with the module. For our project we use the **Nucleo F103RB** board and the TX/RX pins are connected to the *UART2* (TODO) interface.\
For testing purposes and example code the projects `periph_uart` and `periph_uart_mode` inside the `tests` directory of the RIOT project can be used.\

For serial commands see the [PMTK command packet datasheet](https://cdn-shop.adafruit.com/datasheets/PMTK%20command%20packet-Complete-C39-A01.pdf).

### Commands sent to the GPS module
- `225 PMTK_CMD_PERIODIC_MODE`: Enter Standby or Backup mode for power saving
- `251 PMTK_SET_NMEA_BAUDRATE`: Set Baudrate

### Data to be sent from the GPS module (to be implemented in code via RIOT)
- `010 PMTK_SYS_MSG`: Output system message (3 = module is in "Normal" mode)