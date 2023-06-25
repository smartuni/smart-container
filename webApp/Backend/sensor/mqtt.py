import uuid
import datetime
from django.forms import ValidationError
import paho.mqtt.client as mqtt
import json
import os
from cbor2 import loads
import base64
from .models import Container, SensorData
from django.db import IntegrityError
from django.core.exceptions import ValidationError
from kpn_senml import *




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
    owner_instance = Container.objects.get(container_id=SensorData.owner)
    if time is None or sensorData is None or sensorType is None or owner_instance is None:
        raise (ValueError("One or more parameters are None"))
    try:
        entry = sensorData.objects.create(
            id=uuid.uuid4(),
            sensor_type=sensorType,
            sensor_data=sensorData,
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


# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    # Parse Byte data converted to JSON
    # payload = json.loads(msg.payload.decode("utf-8"))
    doc = SenmlPack('Payload')
    doc.add(msg)

    print(doc)
    # print(msg.topic+" "+str(msg.payload))
    print(process_message(msg))


# {
# 	sensor: string
# 	value: number
# 	unit: string
# 	time: string
# }

# Parsing the payload message for the data we want
def process_message(msg):
    msg = [{-2: "gps", 6: 6, 3: "1234.5678,1234.5678"}, {-2: "crash", 6: 1, 4: True}, {-2: "hum", 6: 2, 2: 61}]
    # Decode the SenML message
    # Convert SenML data to JSON format
    # payload = json.dumps(msg)
    doc = SenmlPack('Payload')
    doc.add(msg)
    json_data = doc.to_json()

    # Extract values from the first SenML data object
    # Extracts GPS
    first_senml_data = json_data[0]
    value = first_senml_data[3]
    sensor = first_senml_data[-2]
    current_time = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    
    print("Current Time:", current_time)
    print("GPS Value:", value)
    print("Sensor Type:", sensor)

    # Print the decoded SenML message
    print("=============================================")
    print(doc.to_json())



    # payload = json.loads(msg.payload.decode("utf-8"))
    # # Extract temperature and humidity data

    # sensor = payload['sensor']
    # value = payload['value'] + payload['unit']
    # time = payload['time']

    # return postToDatabase(sensor, value, time)
    

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

file = open("mqtt.txt", "w")
file.write("MQTT started execution....")
file.close()

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
