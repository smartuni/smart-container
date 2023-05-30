## Accelerometer Test

This program is using the lis2dh12 sensor (SEN0224 shield) to detect impacts. 

The sensor is continuously reading the acceleration data and stores them in a FIFO with 32 elements. 

The sensor is configured to generate an interrupt if a defined threshold acceleration in specified axis is exceeded. The interrupt is generated using a dedicated GPIO Pin. The microcontroller waits for the interrupt to occur (mutex lock), if it occurs, the interrupt is reset and the 32 Data of the FIFO are read and printed. 

The usage of the functions is mostly derivated from RIOT/tests/driver_lis2dh12.

Power consumption:

The Accelerometer shield consumes about 1.178 mA at 3.3V (3.297V). This is after the power off command was sent, SDC and SDA are constant high after that, no data are transmitted. May be caused by the LDO on the shield, Datasheet says about 6 µA consumption. 

Some more measurements that are temporarily stored here:

4.2V, 1.219mA (µC)
3.3V, 1.186mA (shield)

In Total (Shield on 3V board supply) -> 4.2V, 2.3mA
1 Hz -> 4.2V, 2.7mA
Very high -> 4.2V, 2.48mA, up to 3.7mA while interrupt occurs
