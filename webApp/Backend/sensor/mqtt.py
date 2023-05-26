import uuid
import paho.mqtt.client as mqtt
import json
from .models import SensorData
from .serializer import SensorSerializer
from django.db.utils import IntegrityError
from django.core.exceptions import ValidationError

# Confiugure as needed
USERNAME = "mqtt@thingsnet"
API_KEY = "NNSXS.2NMGH2LIBMJPRMEGCE77IGSVTLF47LGQMTY7XTA.T4TBPJ6BYCV43QFGAX3AXNGC6WW4HE6QY3XRKOR4J47C7QFB4VNA"


# Subscribe to the uplink topic of all devices
TOPIC = f"v3/{USERNAME}/devices/+/up"


# Address of TTN MQTT server
TTN_MQTT_SERVER = "mobi35.inet.haw-hamburg.de"


def postToDatabase(time, data, dataType, owner):
    """
    Post the data to the database
    """
    try:
        entry = SensorData.objects.create(
            sensor_id=uuid.uuid4(),
            sensor_type=dataType,
            sensor_data=data,
            sensor_time=time,
            owner=owner,
        )
        entry.save()
    except ValueError as e:
        print(e)
    except IntegrityError as e:
        print(e)
    except ValidationError as e:
        print(e)


# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))

    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe("#")


# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    # Parse Byte data converted to JSON
    payload = json.loads(msg.payload.decode("utf-8"))
    print(payload)
    # print(msg.topic+" "+str(msg.payload))
    print(process_message(msg))


# Parsing the payload message for the data we want
def process_message(msg):
    payload = json.loads(msg.payload.decode("utf-8"))
    # Extract temperature and humidity data
    time = payload["received_at"]

    temperature = payload["uplink_message"]["decoded_payload"]["temperature"]["value"]
    temperature_unit = payload["uplink_message"]["decoded_payload"]["temperature"][
        "unit"
    ]
    temperature_str = str(temperature) + " " + temperature_unit

    humidity = payload["uplink_message"]["decoded_payload"]["humidity"]["value"]
    humidity_unit = payload["uplink_message"]["decoded_payload"]["humidity"]["unit"]
    humidity_str = str(humidity) + " " + humidity_unit

    return time, temperature_str, humidity_str


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
