import sqlite3
import secrets
import serial
import time
import logging

logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')

def provision_device(device_id, ser):
    dtls_psk_aes_128_key = secrets.token_hex(16)
    
    try:
        data = f'{device_id}{dtls_psk_aes_128_key}'

        db.execute('INSERT INTO provision (device_id, dtls_psk_aes_128_key) VALUES (?, ?)', 
                   (device_id, dtls_psk_aes_128_key))

        ser.write(data.encode())
        while ser.out_waiting > 0:
            time.sleep(0.01)

        ack = ser.readline().decode().strip()
    except serial.SerialException as e:
        logging.error(f"Serial communication error: {e}")

    if ack != "ACK":
        logging.error(f"Device {device_id} provisioning failed. Retrying...")
        provision_device(device_id, ser)  
        return

with sqlite3.connect('provision.db') as conn:
    db = conn.cursor()
    db.execute('CREATE TABLE IF NOT EXISTS provision (device_id INTEGER PRIMARY KEY, dtls_psk_aes_128_key TEXT)')

    try:
        with serial.Serial('COM6', 115200, timeout=1) as ser:
            for device_id in range(1, 4):  # Change to only provision 3 devices
                provision_device(device_id, ser)
    except serial.SerialException as e:
        logging.error(f"Serial communication error: {e}")

    conn.commit()
