import secrets
import time
import serial

ser = serial.Serial('/dev/tty.usbmodem14101', 115200, timeout=1)
time.sleep(2)  # Wait

for i in range(5):  
    key = secrets.token_hex(16)  # AES-128 key
    ser.write((key + '\n').encode())  # Send key
    print(f"Sent key #{i+1}: '{key}'")
    
    # Wait for 'ACK' from device
    ack = ser.readline().decode().strip()
    if ack == 'ACK':
        print("ACK received from device\n")
    else:
        print("No ACK received. Something went wrong!\n")

    time.sleep(1)  # Wait between sending keys
ser.close()
