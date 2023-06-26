import sqlite3
import secrets
import serial
import time
import logging

logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')

def provision_device(device_id, ser):
    dtls_psk_aes_128_key = secrets.token_hex(16)
    ieee802154_key = secrets.token_hex(16)
    concentrator_ipv6 = '0'
    sec_save_aes_key = secrets.token_hex(16)

    try:
        # Store these keys into SQLite DB for later retrieval
        db.execute('INSERT INTO provision (device_id, ieee802154_key, concentrator_ipv6, dtls_psk_aes_128_key, sec_save_aes_key) VALUES (?, ?, ?, ?, ?)',
                   (device_id, ieee802154_key, concentrator_ipv6, dtls_psk_aes_128_key, sec_save_aes_key))
        
        # Send provisioning command to the device
        cmd = f"provisioning {device_id} {ieee802154_key} {concentrator_ipv6} {dtls_psk_aes_128_key} {sec_save_aes_key}\n"
        ser.write(cmd.encode())
        time.sleep(0.01)

    except serial.SerialException as e:
        logging.error(f"Serial communication error: {e}")
    except sqlite3.Error as e:
        logging.error(f"Database error: {e}")
    except Exception as e:
        logging.error(f"Unexpected error: {e}")


with sqlite3.connect('provision.db') as conn:
    db = conn.cursor()
    db.execute('DROP TABLE provision')
    db.execute('CREATE TABLE IF NOT EXISTS provision (device_id INTEGER PRIMARY KEY, ieee802154_key TEXT, concentrator_ipv6 TEXT, dtls_psk_aes_128_key TEXT, sec_save_aes_key TEXT)')

    try:
        with serial.Serial('/dev/tty.usbmodem14101', 115200, timeout=1) as ser:  
            for device_id in range(1, 3):
                provision_device(device_id, ser)
                
    except serial.SerialException as e:
        logging.error(f"Serial communication error: {e}")
    except sqlite3.Error as e:
        logging.error(f"Database error: {e}")
    except Exception as e:
        logging.error(f"Unexpected error: {e}")

    conn.commit()
