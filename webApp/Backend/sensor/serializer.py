from rest_framework import serializers
from rest_framework_simplejwt.serializers import TokenObtainPairSerializer
from rest_framework.validators import UniqueValidator
from django.contrib.auth.password_validation import validate_password
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



# * __Authentication Serializers___________________________________________________________________

class MyTokenObtainPairSerializer(TokenObtainPairSerializer):

    @classmethod
    def get_token(cls, user):
        token = super(MyTokenObtainPairSerializer, cls).get_token(user)

        # Add custom claims
        token['username'] = user.email
        token['firstName'] = user.firstName
        token['lastname'] = user.lastName
        return token

class RegisterSerializer(serializers.ModelSerializer):
    email = serializers.EmailField(required=True, validators=[UniqueValidator(queryset=User.objects.all())])
    password = serializers.CharField(write_only=True, required=True, validators=[validate_password])

    class Meta:
        model = User
        fields = ["firstName", "lastName", "email", "password", "company", "role"]
        extra_kwargs = {
            "role": {"required": False}
        }

    def create(self, validated_data):
        print(validated_data)
        user = User.objects.create(
            email=validated_data['email'],
            firstName=validated_data['firstName'],
            lastName=validated_data['lastName'],
            company=validated_data['company'],
            role=validated_data.get('role', "Guest")
        )
        
        user.set_password(validated_data['password'])
        user.save()

        return user