from django.db import models

class Container(models.Model):
    id = models.UUIDField
    start = models.CharField(max_length=256)
    dest = models.CharField(max_length=256)
    door_status = models.BooleanField
    content = models.CharField(max_length=1024)
    userId = models.UUIDField
    crashed = models.BooleanField
    threshold = models.JSONField

    def __str__(self):
        return self.id
    
    class Meta:
        ordering = ['id']

class SensorData(models.Model):
    id = models.UUIDField
    data_type = models.CharField(max_length=64)
    value = models.CharField(max_length=1024)
    datetime = models.DateTimeField
    container_id = models.UUIDField

class User(models.Model):
    id = models.UUIDField
    firstName = models.CharField(max_length=256)
    lastName = models.CharField(max_length=256)
    email = models.CharField(max_length=256)
    password = models.CharField(max_length=128)
    company = models.CharField(max_length=128)
    role = models.CharField(max_length=32)