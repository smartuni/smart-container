import secrets
import serial

def provision_device(device_id, ser):
    dtls_psk_aes_128_key = secrets.token_hex(16)

    try:
        data = f'{device_id},{dtls_psk_aes_128_key}\n'
        ser.write(data.encode())

        ack = ser.readline().decode().strip()
        
    except serial.SerialException as e:
        print(f"Serial communication error: {e}")

    if ack != "ACK":
        print(f"Device {device_id} provisioning failed. Retrying...")
        provision_device(device_id, ser)  

with serial.Serial('COM6', 115200, timeout=1) as ser:
    provision_device(1, ser)  # Provision device 1
