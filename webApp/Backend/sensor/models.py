from django.db import models


# Create your models here.
class Sensor_Data(models.Model):
    sensor_type = models.CharField(max_length=10)
    sensor_data = models.CharField(max_length=100)
    sensor_time = models.DateTimeField()

    class Meta:
        ordering = ["sensor_time"]


class Container(models.Model):
    container_id = models.IntegerField()
    container_content = models.CharField(max_length=100)
    container_door_closed = models.BooleanField()
    container_start = models.CharField()
    container_destination = models.CharField()
    container_time = models.DateTimeField()

    class Meta:
        ordering = ["container_id"]


class User(models.Model):
    user_id = models.IntegerField()
    firstName = models.CharField(max_length=100)
    lastName = models.CharField(max_length=100)
    email = models.CharField(max_length=100)
    password = models.CharField(max_length=100)
    company = models.CharField(max_length=100)
    role = models.CharField(max_length=100)

    class Meta:
        ordering = ["user_id"]
