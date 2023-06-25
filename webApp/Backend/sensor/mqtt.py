import binascii, json, base64, uuid, datetime
from django.forms import ValidationError
import paho.mqtt.client as mqtt
from cbor2 import loads
from sensor.models import Container, SensorData 
from django.db import IntegrityError
from django.core.exceptions import ValidationError
from kpn_senml import *

file = open("mqtt.txt", "w")
file.write("MQTT started execution....")
file.close()


# Confiugure as needed
USERNAME="mqtest2@thingsnet"
API_KEY="NNSXS.K2TY66DR7XTMNWRGFQIC6H2MJSWDH2L4JHLKT6Q.IMEQNYYILH24PW5NSOYSEKMG6XLYKKI6G2JSEZBNJ2GGB2OYTODQ"


# Subscribe to the uplink topic of all devices
TOPIC = f"v3/{USERNAME}/devices/+/up"


# Address of TTN MQTT server
TTN_MQTT_SERVER = "mobi35.inet.haw-hamburg.de"


def postToDatabase(sensorType, sensorData, time):
    """
    The function then creates a new SensorData object using the SensorData.objects.create() method.
    The SensorData object has five fields: id, sensor_type, sensor_data, sensor_time, and owner.
    The id field is a UUID field that serves as the primary key for the table.
    The sensor_type field is a character field that stores the type of sensor. The sensor_data field is a character field that stores the data from the sensor.
    The sensor_time field is a date-time field that stores the time the data was recorded.
    The owner field is a foreign key to the Container model, which represents the container that the sensor is attached to.
    """
    owner_instance = Container.objects.get(container_id=uuid.UUID('30676a11-4342-4c12-8a5c-720d9515115a')) 
    if time is None or sensorData is None or sensorType is None or owner_instance is None:
        raise (ValueError("One or more parameters are None"))
    try:
        entry = SensorData.objects.create(
            id=uuid.uuid4(),
            sensor_type=sensorType,
            sensor_data=str(sensorData),
            sensor_time=time,
            owner=owner_instance,
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

# Parsing the payload message for the data we want
def process_message(client, userdata, msg):
    msg_decoded = msg.payload.decode("utf-8")
    output_dict = json.loads(msg_decoded)
    decoded_payload = base64.b64decode(output_dict["uplink_message"]["frm_payload"])

    decoded_cbor_data = binascii.unhexlify(binascii.hexlify(decoded_payload))
    json_data = loads(decoded_cbor_data)

    for entry in json_data:
        sensor_type = entry[-2]
        
        if 2 in entry:
            #Integer
            sensor_data = entry[2]
        elif 3 in entry:
            #String
            sensor_data = entry[3]
        elif 4 in entry:
            #Boolean
            sensor_data = entry[4]
        else:
            sensor_data = None
        sensor_time = datetime.datetime.now() 
        postToDatabase(sensor_type, sensor_data, sensor_time)
    

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = process_message


# client = mqtt.Client()
# client.on_connect = on_connect
# client.on_message = on_message


client.username_pw_set(USERNAME, API_KEY)
client.connect(TTN_MQTT_SERVER, 80, 60)


# Blocking call that processes network traffic, dispatches callbacks and
# handles reconnecting.
# Other loop*() functions are available that give a threaded interface and a
# manual interface.
client.loop_forever()
# if __name__ == "__main__":
#     print("Test")
#     postToDatabase("time", "data", "dataType", "owner")
