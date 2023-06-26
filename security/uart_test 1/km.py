import secrets
import time
import serial

# Create the serial object
ser = serial.Serial('/dev/tty.usbmodem14101', 115200, timeout=1)
time.sleep(2)  # Wait for the connection to be established

# Generate an AES key
aes_key = secrets.token_hex(16)
print(f"Generated AES key: '{aes_key}'")

# Specify the device ID
device_id = 1
print(f"Device ID: {device_id}")

# Send the device ID
ser.write(f"{device_id}\n".encode())
time.sleep(1)  # Wait for the device to process the ID

# Send the AES key
ser.write((aes_key + '\n').encode())
print("AES key sent to device.")

# Wait for 'ACK' from the device
ack = ser.readline().decode().strip()
if ack == 'ACK':
    print("ACK received from device.")
else:
    print("No ACK received. Something went wrong!")

# Close the serial connection
ser.close()
