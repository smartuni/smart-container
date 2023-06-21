from sensor.models import *
import uuid, datetime
from datetime import timedelta


containerContents = ["Carrots", "Cucumbers", "Onions", "Garlic", "Tomatoes"]
containerStarts = ["Berlin", "Hamburg", "Munich", "Cologne", "Frankfurt"]
containerDestinations = ["Hamburg", "Munich", "Cologne", "Frankfurt", "Berlin"]
containerDoorClosed = [True, False, True, False, True]

yesterday = datetime.datetime.now() - timedelta(days=1)
dates = [yesterday + timedelta(hours=i) for i in range(0, 24)]


for i in range(0, 5):
    container = Container.objects.create(
        container_id=uuid.uuid4(),
        container_content=containerContents[i],
        container_time=datetime.datetime.now(),
        container_start=containerStarts[i],
        container_destination=containerDestinations[i],
        container_door_closed=containerDoorClosed[i],
    )
    container.save()
    for j in range(0, 24):
        latitude = 52.520008 + (j * 0.0001) + (i * 1)
        longitude = 13.404954 + (j * 0.0001) + (i * 1)
        temp = 20 + (j * 0.1) + (i * 1)
        humidity = 50 + (j * 0.1) + (i * 1)
        door = False if j < 12 and i == 4 else True
        acceleration = 0 + (j * 0.1) + (i * 1)
        water_leak = True if j >= 22 and i == 3 else False

        sensor = SensorData.objects.create(id=uuid.uuid4(), sensor_time=dates[j], sensor_type="GPS", sensor_data=f"{latitude}, {longitude}", owner=container)
        sensor.save()
        sensor = SensorData.objects.create(id=uuid.uuid4(), sensor_time=dates[j], sensor_type="TEMP", sensor_data=f"{temp}", owner=container)
        sensor.save()
        sensor = SensorData.objects.create(id=uuid.uuid4(), sensor_time=dates[j], sensor_type="HUM", sensor_data=f"{humidity}", owner=container)
        sensor.save()
        sensor = SensorData.objects.create(id=uuid.uuid4(), sensor_time=dates[j], sensor_type="DOOR", sensor_data=f"{door}", owner=container)
        sensor.save()
        sensor = SensorData.objects.create(id=uuid.uuid4(), sensor_time=dates[j], sensor_type="ACCEL", sensor_data=f"{acceleration}", owner=container)
        sensor.save()
        sensor = SensorData.objects.create(id=uuid.uuid4(), sensor_time=dates[j], sensor_type="LEAK", sensor_data=f"{water_leak}", owner=container)
        sensor.save()


