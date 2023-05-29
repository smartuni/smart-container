from rest_framework import serializers
from .models import SensorData, User, Container


from django.contrib.auth.hashers import make_password


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
    class Meta:
        model = User
        fields = ["firstName", "lastName", "email", "password"]
        extra_kwargs = {"password": {"write_only": True}}

    def create(self, validated_data):
        validated_data["password"] = make_password(validated_data["password"])
        return super(UserSerializer, self).create(validated_data)


class SignInSerializer(serializers.Serializer):
    email = serializers.CharField()
    password = serializers.CharField()
