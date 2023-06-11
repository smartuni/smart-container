# Calculations for power consumption

The sensornodes will be driven by battery, the concentrator may be connected differently. However the concentrater has a much higher power consumption so much energy is needed for long term usage. May be provided by a car battery. 

The feathers will get a battery, which should provide power for about 30 days. The boards sleep most of the time, the external shields for the sensors are consuming a bit extra. 

If the board is sleeping, it consumes about 1.3 mA @4.2 V. The final battery voltage will be around 3.7 V. 

The power consumption was measured using the power supply so the results may be inaccurate due to the small currents. 

## Different sensors

The datasheet of the bme280 shield specifies a working current of 2 mA. The working voltage is between 3.3 V and 5 V. 

The accelerometer consumes about 1.2 mA@4.2 V all the time (measured with power supply). Board and accelerometer consumed about 2.3 mA@ 4.2 V. 

The reed switch won't consume any power while being open. A high resistance in series will limit the current if the switch is closed. 

The gps module theoretically consumes 20-25 mA. It won't be up all the time but getting satellites after power off take some time so this node will have the highest consumption of all. 

The waterleak sensor has high resistances in between and the signal will be digitalized using a Schmitt-Trigger IC (inverted). There will be a constant (small) current flow. 

The shields will be powered using the 3.3 V output of the feather board. 

## Calculation

The calculations are for 30 days with a constant current flow. 

| Current in mA | Electric charge in Ah | Energy in Wh |
|---------------|-----------------------|--------------|
| 2             | 1.44                  | 5.33         |
| 5             | 3.6                   | 13.32        |
| 7             | 5.04                  | 18.65        |
| 10            | 7.2                   | 26.64        |
| 20            | 14.4                  | 53.28        |
| 30            | 21.6                  | 79.92        |

An easy and cheap solution is using 18650 cells in parallel depending on the estimated power consumption. 
In theory the cells can be charged using the feather board but that may take a lot of time because the charging current is limited to 100 mA. 
