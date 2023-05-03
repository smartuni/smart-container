from django.db import models

# Create your models here.
class Sensor_Data(models.Model):
    sensor_type = models.CharField(max_length=10)
    sensor_data = models.CharField(max_length=100)
    sensor_time = models.DateTimeField()

    class Meta:
        ordering = ['sensor_time']


class Container(models.Model):
    container_id = models.IntegerField()
    container_content = models.CharField(max_length=100)
    container_door_closed = models.BooleanField()
    container_start = models.CharField()
    container_destination = models.CharField()
    container_time = models.DateTimeField()

    def __str__(self):
        return self.container_id
    
    class Meta:
        ordering = ['container_id']
