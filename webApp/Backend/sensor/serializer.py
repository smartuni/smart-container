from rest_framework import serializers
from .models import SensorData, User, Container


class SensorSerializer(serializers.ModelSerializer):
    """
    Serializer class for the SensorData model
    """

    class Meta:
        model = SensorData
        fields = ["id", "sensor_type", "sensor_data", "sensor_time", "owner"]


class ContainerSerializer(serializers.ModelSerializer):
    """
    Serializer class for the Container model
    """

    sensor_data = serializers.PrimaryKeyRelatedField(
        many=True, queryset=SensorData.objects.all()
    )

    class Meta:
        model = Container
        fields = [
            "container_id",
            "container_content",
            "container_door_closed",
            "container_start",
            "container_destination",
            "container_time",
            "sensor_data",
        ]


class UserSerializer(serializers.ModelSerializer):
    """
    Serializer class for the User model
    """

    class Meta:
        model = User
        fields = [
            "user_id",
            "firstName",
            "lastName",
            "email",
            "password",
            "company",
            "role",
        ]
