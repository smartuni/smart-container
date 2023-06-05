# BME280

This is an example for reading data via I2C from the BME280 using Saul.

The BME280 measures temperature, humidity and pressure. It can be connected via I2C or SPI (I2C is used here).

The values are printed to the console using `phydat_dump`, the values may be extracted separately from the struct (datatype of value is int16_t).

The values are read every second. 