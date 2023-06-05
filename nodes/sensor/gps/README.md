# GPS Sensor

GPS Sensor RIOT application.

# Example

```shell
➜  gps git:(gps_sensor) ✗ sudo make term PORT=/dev/ttyACM1
/home/maik/Projects/HAW/smart-container/nodes/RIOT/dist/tools/pyterm/pyterm -p "/dev/ttyACM1" -b "115200"
Twisted not available, please install it if you want to use pyterm's JSON capabilities
2023-05-29 21:14:12,966 # Connect to serial port /dev/ttyACM1
Welcome to pyterm!
Type '/exit' to exit.
2023-05-29 21:14:13,970 # main(): This is RIOT! (Version: 2023.07-devel-325-g2863d-HEAD)
2023-05-29 21:14:14,588 # ===================================
2023-05-29 21:14:14,589 # SMARTCONTAINER GPS SENSOR
2023-05-29 21:14:14,591 # ===================================
2023-05-29 21:14:14,592 # Success: Initialized UART_DEV(0) at 9600 baud
2023-05-29 21:14:15,377 # [GPCGA] latitude=53.572063; longitude=10.085766
2023-05-29 21:14:15,430 # [GPGSA] sats=11; mode=A; fix_type=3
2023-05-29 21:14:15,507 # [GPRMC] valid=true; latitude=53.572063; longitude=10.085766; speed=0.14; date: 29.05.2023
2023-05-29 21:14:15,547 # [GPVTG] faa_mode=65; magnetic_track_degrees=; true_track_degrees=
2023-05-29 21:14:16,389 # [GPCGA] latitude=53.572063; longitude=10.085766
2023-05-29 21:14:16,442 # [GPGSA] sats=11; mode=A; fix_type=3
2023-05-29 21:14:16,516 # [GPGSV] total_sats=7; total_msgs=2; msg_nr=1
2023-05-29 21:14:16,571 # [GPGSV] total_sats=7; total_msgs=2; msg_nr=2
2023-05-29 21:14:16,647 # [GPRMC] valid=true; latitude=53.572063; longitude=10.085766; speed=0.19; date: 29.05.2023
2023-05-29 21:14:16,688 # [GPVTG] faa_mode=65; magnetic_track_degrees=; true_track_degrees=
2023-05-29 21:14:17,356 # [GPCGA] latitude=53.572063; longitude=10.085764
2023-05-29 21:14:17,408 # [GPGSA] sats=11; mode=A; fix_type=3
2023-05-29 21:14:17,485 # [GPRMC] valid=true; latitude=53.572063; longitude=10.085764; speed=0.15; date: 29.05.2023
2023-05-29 21:14:17,526 # [GPVTG] faa_mode=65; magnetic_track_degrees=; true_track_degrees=
2023-05-29 21:14:18,437 # [GPCGA] latitude=53.572063; longitude=10.085762
2023-05-29 21:14:18,490 # [GPGSA] sats=11; mode=A; fix_type=3
2023-05-29 21:14:18,567 # [GPRMC] valid=true; latitude=53.572063; longitude=10.085762; speed=0.04; date: 29.05.2023
```

# Usage

1. Build and flash
   `make all flash`

1. (Optionally) Run Shell
   `sudo make term`
