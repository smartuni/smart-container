import secrets
import time
import serial


def main():
   
# Generate AES key
    aes_key = secrets.token_hex(16)
    device_id = 1  # device ID (1-10)
    print(f'Generated key: {aes_key}')
    ser = serial.Serial('/dev/tty.usbmodem143101', 115200, timeout=1)
    ser.isOpen()
    time.sleep(2)  # Wait

# Send the device ID and AES key
#ser.write(f"{device_id}\n".encode())
    ser.write(aes_key.encode())
    time.sleep(1)
    ser.close()
    num_bytes = ser.write(aes_key.encode())
    if num_bytes != len(aes_key):
        print("Error: Not all bytes were sent!")


if __name__ == '__main__':
    main()