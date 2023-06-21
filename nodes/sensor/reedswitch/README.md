## Reed Switch

The program sleeps until a falling edge is detected. It then sends a data stream to the concentrator. 

The resistence of the reed-switch is in the megaohm range, if there is no magnet nearby and lowers to 10k to 100k,
depending on the magnet and its position. 

The falling resistance should be enough, the final node is not tested yet. 
The internal GPIO Pin is configured as Pull-up so no external resistors are needed. 

If this is not working, the pull up resistor has to be replaced by an external resistor with
a resistance of around 500k to 1M. 