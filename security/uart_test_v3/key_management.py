import serial
import secrets
SERIAL_PORT = '/dev/tty.usbmodem14401'  
BAUD_RATE = 96000


def generate_key():
    return secrets.token_bytes(16)

def send_key(key):
    try:
        # Open the serial port
        with serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1) as ser:
            # Send the key
            ser.write(key)

        print(f"Successfully sent key: {key}")

    except serial.SerialException as e:
        print(f"An error occurred: {str(e)}")

if __name__ == "__main__":
    key = generate_key()
    send_key(key)
