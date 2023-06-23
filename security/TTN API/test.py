import requests
import json


API_BASE_URL = 'https://eu1.thethings.network:8094'  # HTTPS
#API_BASE_URL = 'http://eu1.thethings.network:8084'  # HTTP
APP_ID = 'topsecret'  # Replace with your TTN application ID
ACCESS_KEY = ''  # Replace with your access key


def get_device_info(device_id):
    headers = {
        'Authorization': f'Bearer {ACCESS_KEY}',
        'Accept': 'application/json',
        'User-Agent': 'python-requests',  # Recommended user-agent
    }

    response = requests.get(f'{API_BASE_URL}/applications/{APP_ID}/devices/{device_id}', headers=headers)

    if response.status_code == 200:
        return response.json()
    
    else:
        print(f"Failed to retrieve device info: {response.text}")
        return None

device_info = get_device_info('your-device-id')  # Replace 'your-device-id' with the actual device ID
if device_info is not None:
    print(json.dumps(device_info, indent=4))


