import secrets
import time
import serial

ser = serial.Serial('/dev/tty.usbmodem14301', 115200, timeout=1)
time.sleep(2)  # Wait

for i in range(1, 15):  # Send a 15 times
    ser.write(f'a{i}\n'.encode())  
    print(f"Sent char #{i}: 'a'")
    time.sleep(1)  # Wait
ser.close()
