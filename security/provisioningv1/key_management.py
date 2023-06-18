import sqlite3
import secrets
import binascii
import serial
import time
import logging

logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')

def provision_device(device_id, ser):
    dtls_psk_aes_128_key = secrets.token_hex(16)
    sec_save_aes_key = secrets.token_hex(16)
    ieee802154_key = secrets.token_hex(16)  
    lorawan_dev_eui = secrets.token_hex(16)
    lorawan_app_eui = secrets.token_hex(16)
    lorawan_app_key = secrets.token_hex(32)
  
    ack = ''
    try:
        cpuid = ser.readline().decode().strip()
        ipv6_addr_concentrator = ser.readline().decode().strip()

        data = (f'{dtls_psk_aes_128_key}'
                f'{sec_save_aes_key}'
                f'{ieee802154_key}'
                f'{lorawan_dev_eui}'
                f'{lorawan_app_eui}'
                f'{lorawan_app_key}'
                f'{ipv6_addr_concentrator}')

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

    db.execute('INSERT INTO provision (device_id, dtls_psk_aes_128_key, sec_save_aes_key, ieee802154_key, lorawan_dev_eui, lorawan_app_eui, lorawan_app_key, ipv6_addr_concentrator) VALUES (?, ?, ?, ?, ?, ?, ?, ?)',
               (device_id, dtls_psk_aes_128_key, sec_save_aes_key, ieee802154_key, lorawan_dev_eui, lorawan_app_eui, lorawan_app_key, ipv6_addr_concentrator))

with sqlite3.connect('provision.db') as conn:
    db = conn.cursor()
    db.execute('CREATE TABLE IF NOT EXISTS provision (device_id INTEGER PRIMARY KEY, dtls_psk_aes_128_key TEXT, sec_save_aes_key TEXT, ieee802154_key TEXT, lorawan_dev_eui TEXT, lorawan_app_eui TEXT, lorawan_app_key TEXT, ipv6_addr_concentrator TEXT)')

    try:
        with serial.Serial('COM6', 115200, timeout=1) as ser:
            for device_id in range(1, 11):
                provision_device(device_id, ser)
    except serial.SerialException as e:
        logging.error(f"Serial communication error: {e}")

    conn.commit()
