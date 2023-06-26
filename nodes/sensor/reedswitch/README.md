## Reed Switch

The program sleeps until a falling edge is detected. It then sends a data stream to the concentrator. 

The resistence of the reed-switch is in the megaohm range, if there is no magnet nearby and lowers to 10k to 100k,
depending on the magnet and its position. 

The internal GPIO Pin is configured as Pull-up so no external resistors are needed. 

If there is a falling edge detected and the read value of the pin is low, the node sends "door closed" to the concentrator. 
If the edge is rising and the read value is not low, it sends "door opened". 
