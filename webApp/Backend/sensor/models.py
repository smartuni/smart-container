from django.db import models
import uuid


# Create your models here.
class Sensor_Data(models.Model):
    """
    Model class for the storing of sensor data
    owner: the container that the sensor is attached to
    sensor_type: the type of sensor
    sensor_data: the data from the sensor
    sensor_time: the time the data was recorded
    """

    owner = models.ForeignKey(
        "Container", related_name="sensor_data", on_delete=models.CASCADE
    )
    sensor_type = models.CharField(max_length=10)
    sensor_data = models.CharField(max_length=100)
    sensor_time = models.DateTimeField()

    class Meta:
        ordering = ["sensor_time"]


class Container(models.Model):
    """
    Model class for the storing of container data
    container_id: the id of the container
    container_content: the contents of the container
    container_door_closed: whether the door is closed or not
    container_start: the starting location of the container
    container_destination: the destination of the container
    container_time: the time the container was loaded and shipped
    """

    container_id = models.UUIDField(
        primary_key=True, default=uuid.uuid4, editable=False
    )
    container_content = models.CharField(max_length=100)
    container_door_closed = models.BooleanField()
    container_start = models.CharField(max_length=100)
    container_destination = models.CharField(max_length=100)
    container_time = models.DateTimeField()

    class Meta:
        ordering = ["id"]


class SensorData(models.Model):
    id = models.UUIDField(primary_key=True, default=uuid.uuid4, editable=False)
    data_type = models.CharField(max_length=64)
    value = models.CharField(max_length=1024)
    datetime = models.DateTimeField
    container_id = models.UUIDField


class User(models.Model):
    """
    Model class for the storing of user data
    user_id: the id of the user
    firstName: the first name of the user
    lastName: the last name of the user
    email: the email of the user
    password: the password of the user
    company: the company the user works for
    role: the role of the user
    """

    user_id = models.IntegerField(primary_key=True, default=uuid.uuid4, editable=False)
    firstName = models.CharField(max_length=100)
    lastName = models.CharField(max_length=100)
    email = models.CharField(max_length=100)
    password = models.CharField(max_length=100)
    company = models.CharField(max_length=100)
    role = models.CharField(max_length=100)

    class Meta:
        ordering = ["user_id"]
