import paho.mqtt.client as mqtt
import json
import base64

# Confiugure as needed
USERNAME="mqtest2@thingsnet"
API_KEY="NNSXS.6ECU4JWA34XHEA5MEU52KFJPKBRVBLJTYU5JLUY.3QZHHDPDTVUT7F6EZ5DFFQ6FGSRCMQ3FL57CAMTOAWXIDOLYBZDA"


# Subscribe to the uplink topic of all devices
TOPIC = f"v3/{USERNAME}/devices/+/up"


# Address of TTN MQTT server
TTN_MQTT_SERVER = "mobi35.inet.haw-hamburg.de"


# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))


# Subscribing in on_connect() means that if we lose the connection and
# reconnect then subscriptions will be renewed.
    client.subscribe("#")



# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    # Parse Byte data converted to JSON
    payload = json.loads(msg.payload.decode('utf-8'))
    print(payload)
    #print(msg.topic+" "+str(msg.payload))
    print(process_message(msg))

# Parsing the payload message for the data we want
def process_message(msg):
    payload = json.loads(msg.payload.decode('utf-8'))
    # Extract temperature and humidity data

    time = payload['received_at']
    
    message = payload['uplink_message']['frm_payload']
    # Convert base64 encoded string to bytes
    bytes_data = base64.b64decode(message)
    # Convert bytes to string
    decoded_message = bytes_data.decode('utf-8')

    # temperature = payload['uplink_message']['decoded_payload']['temperature']['value']
    # temperature_unit = payload['uplink_message']['decoded_payload']['temperature']['unit']
    # temperature_str = str(temperature) + " " + temperature_unit

    # humidity = payload['uplink_message']['decoded_payload']['humidity']['value']
    # humidity_unit = payload['uplink_message']['decoded_payload']['humidity']['unit']
    # humidity_str = str(humidity) + " " + humidity_unit

    return time, decoded_message
    

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message



client.username_pw_set(USERNAME, API_KEY)
client.connect(TTN_MQTT_SERVER, 80, 60)



# Blocking call that processes network traffic, dispatches callbacks and
# handles reconnecting.
# Other loop*() functions are available that give a threaded interface and a
# manual interface.
client.loop_forever()