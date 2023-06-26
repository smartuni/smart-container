import sqlite3
import secrets
import serial
import time
import logging
import requests
import json

logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')


API_BASE_URL = 'https://eu1.thethings.network:8094' 
APP_ID = 'topsecret'  #  TTN application ID
ACCESS_KEY = 'xxx'  

def provision_device(device_id, ser):
    dtls_psk_aes_128_key = secrets.token_hex(16)
    sec_save_aes_key = secrets.token_hex(16)
    ieee802154_key = secrets.token_hex(16)

    try:
        cpuid = ser.readline().decode().strip()
        ipv6_addr_concentrator = ser.readline().decode().strip()

        # For all devices nodes
        data = (f'{dtls_psk_aes_128_key}'
                f'{sec_save_aes_key}'
                f'{ieee802154_key}')

        db.execute('INSERT INTO provision (device_id, dtls_psk_aes_128_key, sec_save_aes_key, ieee802154_key) VALUES (?, ?, ?, ?)', 
                   (device_id, dtls_psk_aes_128_key, sec_save_aes_key, ieee802154_key))

        # Retrieve the device information from TTN API
        response = requests.get(
            f'{API_BASE_URL}/api/v2/applications/{APP_ID}/devices',
            headers={'Authorization': f'Bearer {ACCESS_KEY}'}
        )

        if response.status_code != 200:
            logging.error(f"Failed to retrieve device info from TTN: {response.text}")
            return

        device_info = response.json()
        lorawan_dev_eui = device_info['dev_eui']
        lorawan_app_eui = device_info['app_eui']
        lorawan_app_key = device_info['app_key']

        if device_id == 10:  # for the main concentrator node
            data += (f'{lorawan_dev_eui}'
                     f'{lorawan_app_eui}'
                     f'{lorawan_app_key}'
                     f'{ipv6_addr_concentrator}')

            # Retrieve all keys from the database
            keys = db.execute('SELECT dtls_psk_aes_128_key, sec_save_aes_key FROM provision').fetchall()

            # Concatenate all keys
            for key in keys:
                data += "".join(key)

        ser.write(data.encode())
        while ser.out_waiting > 0:
            time.sleep(0.01)

        ack = ser.readline().decode().strip()
        
    except serial.SerialException as e:
        logging.error(f"Serial communication error: {e}")
    except sqlite3.Error as e:
        logging.error(f"Database error: {e}")
    except Exception as e:
        logging.error(f"Unexpected error: {e}")

    if ack != "ACK":
        logging.error(f"Device {device_id} provisioning failed. Retrying...")
        provision_device(device_id, ser)  
        return

with sqlite3.connect('provision.db') as conn:
    db = conn.cursor()
    db.execute('CREATE TABLE IF NOT EXISTS provision (device_id INTEGER PRIMARY KEY, dtls_psk_aes_128_key TEXT, sec_save_aes_key TEXT, ieee802154_key TEXT)')

    try:
        with serial.Serial('COM6', 115200, timeout=1) as ser:
            for device_id in range(1, 11):
                provision_device(device_id, ser)
                
    except serial.SerialException as e:
        logging.error(f"Serial communication error: {e}")
    except sqlite3.Error as e:
        logging.error(f"Database error: {e}")
    except Exception as e:
        logging.error(f"Unexpected error: {e}")

    conn.commit()