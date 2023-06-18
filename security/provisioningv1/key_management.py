import sqlite3
import secrets
import binascii
import serial
import time

def provision_device(device_id, ser):
    dtls_psk_key = secrets.token_hex(16)
    aes_key = secrets.token_hex(16)
    ieee802154_key = secrets.token_hex(16)  # 128-bit key
    ack = ''

    try:
        cpuid = ser.readline().decode().strip()
        ip = ser.readline().decode().strip()

        if device_id == 1:  # concentrator node device number get LoRaWAN keys
            lorawan_dev_eui = secrets.token_hex(8)
            lorawan_app_eui = secrets.token_hex(8)
            lorawan_app_key = secrets.token_hex(16)
            data = dtls_psk_key + lorawan_dev_eui + lorawan_app_eui + lorawan_app_key + aes_key + ip
        else:
            data = dtls_psk_key + aes_key + ip

        ser.write(data.encode())
        while ser.out_waiting > 0:
            time.sleep(0.01)

        ack = ser.readline().decode().strip()
    except serial.SerialException as e:
        print(f"Serial communication error: {e}")

    if ack != "ACK":
        print(f"Device {device_id} provisioning failed. Retrying...")
        provision_device(device_id, ser)  # Retry provisioning if it fails
        return

    if device_id == 1:
        db.execute('INSERT INTO provision (device_id, dtls_psk_key, lorawan_dev_eui, lorawan_app_eui, lorawan_app_key, aes_key, ip) VALUES (?, ?, ?, ?, ?, ?, ?)',
                   (device_id, dtls_psk_key, lorawan_dev_eui, lorawan_app_eui, lorawan_app_key, aes_key, ip))
    else:
        db.execute('INSERT INTO provision (device_id, dtls_psk_key, aes_key, ip) VALUES (?, ?, ?, ?)',
                   (device_id, dtls_psk_key, aes_key, ip))

with sqlite3.connect('provision.db') as conn:
    db = conn.cursor()
    db.execute('CREATE TABLE IF NOT EXISTS provision (device_id INTEGER PRIMARY KEY, dtls_psk_key TEXT, lorawan_dev_eui TEXT, lorawan_app_eui TEXT, lorawan_app_key TEXT, aes_key TEXT, ip TEXT)')

    try:
        with serial.Serial('COM6', 115200, timeout=1) as ser:
            for device_id in range(1, 11):
                provision_device(device_id, ser)
    except serial.SerialException as e:
        print(f"Serial communication error: {e}")
    
    conn.commit()
