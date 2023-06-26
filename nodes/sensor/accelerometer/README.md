## Accelerometer

This is the final version for the accelerometer sensor node. 
The sensor generates an interrupt, when 10g of acceleration are exceeded.
It then sends a datastream to the concentrator and goes back to sleep. 
The sent stream may be changed.

This program is using the lis2dh12 sensor (SEN0224 shield) to detect impacts. 

There is a FIFO aboard the sensor which may store the last acceleration values, it is possible that the FIFO mode changes after in impact occured so all the accelerations after the impact may be stored. The driver doesn't allow this feature and a manual solution is too slow so the FIFO is bypassed and no values are read. 

The range is +-16g, the Acceleration Threshold value in any direction is hardcoded. 

If an impact occurs, the interrupt pin 1 of the sensor is set high. The interrupt is automatically reset. If there are vibrations that set off the interrupt, many interrupts may occur because the interrupt is reset immediately and the sensor is ready again. Using sleep etc. after an interrupt occured may be useful to stop the µC from spamming. 

There is a 32 element FIFO in which values may be stored, the resolution of the sensor is between 8 and 12 bit. Currently set to 8 bit, frequency can be up to 5 kHz but is set to 1 Hz. Only relevant if any values are read. 

The usage of the functions is mostly derivated from RIOT/tests/driver_lis2dh12.
