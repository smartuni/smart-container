from rest_framework import serializers
from .models import Sensor_Data, User, Container


class SensorSerializer(serializers.ModelSerializer):
    class Meta:
        model = Sensor_Data
        fields = ["id", "sensor_type", "sensor_data", "sensor_time"]


class ContainerSerializer(serializers.ModelSerializer):
    class Meta:
        model = Container
        fields = [
            "id",
            "container_id",
            "container_content",
            "container_door_closed",
            "container_start",
            "container_destination",
            "container_time",
        ]


class UserSerializer(serializers.ModelSerializer):
    class Meta:
        model = User
        fields = [
            "id",
            "user_id",
            "firstName",
            "lastName",
            "email",
            "password",
            "company",
            "role",
        ]
