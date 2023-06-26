# BME280 Humidity via I2C

This is the final program for the bme280 humidity sensor node. 
The humidity data are sent every 10 seconds, the data stream is the humidity with two decimal places.

The function used for the sleep mode is ztimer_periodic_wakeup.