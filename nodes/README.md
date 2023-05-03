# Sensor and Concentrator Node

## Team

- Anton Beck
- Dennis Fischer
- Fabian Schmalenbach
- Maik Lorenz
- Cecdric Michaelis

## What we do

We implement the concentrator node that collects values from multiple sensor nodes (communication via CoAP) and each sensor node. 
The following sensors will be used:

| Sensor Type   | model       | communication  type | Time period  |
|---------------|-------------|---------------------|--------------|
| Temperature   | bme280      | SPI                 | periodically |
| Humidity      | bme280      | SPI                 | periodically |
| GPS           | MTK3339     | UART                | periodically |
| Water leak    | resistor    | Digital read        | On event     |
| Tamper        | reed-switch | Digital read        | On event     |
| Accelerometer | SEN0224     | I2C                 | On event     |

## Sensor node
Adafruit Feather nRF52840 Express

- power via USB or 4.2/3.7V Lipo/Lipoly or LiIon
- Measuring battery voltage with internal ADC (A6 already connected)
- I2C, SPI and UART
- Analog input possible
- information to power consumption cannot be found, the Cortex ARM-M4 may consume a bit but RF52840 takes less energy than a complete WiFi shield. 

## Concentrator node
Nordic semiconductor nRF52840-DK

- capable of CoAP and LoRaWAN (via additional shield)
- external SD-card module for data storage is required

## Communication
- one route per sensor
- discovery per multicast (so sensors discover well-known core of concentrator)
- sensors post their data to concentrator which responds with async acknowledgment
- sensors repeat until they receive ack and then sleep again

## Encryption
...

## TO-DO
- measure power draw of all sensor nodes in "typical"-operation
- implement periodic timer for periodic sensors and interrupts for event sensors
- implement coap communication
- integrate offline storage component provided by Security Team
- add encryption to communication
- implement LoRaWAN with LoRaWAN SSL
- profit
