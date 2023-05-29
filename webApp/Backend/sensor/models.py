from django.db import models
from django.contrib.auth.models import AbstractBaseUser, BaseUserManager

class Container(models.Model):
    id = models.UUIDField
    start = models.CharField(max_length=256)
    dest = models.CharField(max_length=256)
    doorStatus = models.BooleanField
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
    dataType = models.CharField(max_length=64)
    value = models.CharField(max_length=1024)
    datetime = models.DateTimeField
    containerId = models.UUIDField

class User(AbstractBaseUser):
    id = models.UUIDField
    firstName = models.CharField(max_length=256)
    lastName = models.CharField(max_length=256)
    email = models.CharField(max_length=256, unique=True)
    password = models.CharField(max_length=128)
    company = models.CharField(max_length=128)
    role = models.CharField(max_length=32)
    USERNAME_FIELD = "email"
    REQUIRED_FIELDS = ["firstName", "lastName", "company"]
    objects = BaseUserManager()