# BME280 Temperature via I2C

This is the final program for the bme280 temperature sensor node. 
The temperature data are sent every 10 seconds, the data stream is the temperature with two decimal places.

The function used for the sleep mode is ztimer_periodic_wakeup.