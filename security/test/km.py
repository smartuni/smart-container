import secrets
import time
import serial

ser = serial.Serial('/dev/tty.usbmodem14101', 115200, timeout=1)
time.sleep(2)  # Wait

# Generate AES key
aes_key = secrets.token_hex(16)
device_id = 1  # device ID (1-10)

# Send the device ID and AES key
ser.write(f"{device_id}\n".encode())
time.sleep(1)
ser.write(f"{aes_key}\n".encode())
ser.close()
