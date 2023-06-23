import serial
import time

SERIAL_PORT = '/dev/tty.usbmodem14201'  
BAUD_RATE = 96000 
BAUD_RATE = 115200

def send_char(char):
    try:
        with serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1) as ser:
            time.sleep(1) # To ensure the connection is established
            ser.write(char.encode())
            print(f"Successfully sent: '{char}'")

    except serial.SerialException as e:
        print(f"An error occurred: {str(e)}")

if __name__ == "__main__":
    send_char('A')
