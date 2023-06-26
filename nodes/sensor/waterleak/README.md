## Waterleak sensor

The interrupt is falling edge driven because the resistance of the waterleak sensor is falling rapidly
if it is exposed to (mineral)water. The pull up resistor is built externally with a 100k Ohm resistor. 

If the interrupt occurs, a string is sent to the concentrator, that may be changed due to internal conventions. 