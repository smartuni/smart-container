import serial
import time


port = '/dev/tty.usbmodem14201'
baud_rate = 115200

ser = serial.Serial(port, baud_rate, timeout=1)  
def send_data(data):
    try:
        ser = serial.Serial(port,baud_rate , timeout=1)
        ser.flush()
    except Exception as e:
        print(f"Failed to open serial port: {str(e)}")
        return

    if ser.isOpen():
        print("Serial port is open. Sending data...")
        while True:
            try:
                ser.write(data.encode('utf-8'))
                print(f"Data sent: {data}")
                time.sleep(60)  # wait 1 minute
            except Exception as e:
                print(f"Failed to write to serial port: {str(e)}")
                break
        ser.close()
        print("Serial port is closed.")
    else:
        print("Failed to open serial port.")

if __name__ == "__main__":
    send_data('a')