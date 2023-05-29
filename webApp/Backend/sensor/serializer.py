from rest_framework import serializers
from .models import SensorData, User
from django.contrib.auth.hashers import make_password
    
class SensorSerializer(serializers.ModelSerializer):
    class Meta:
        model = SensorData
        fields = ['id', 'data_type', 'value', 'datetime', 'container_id']

class UserSerializer(serializers.ModelSerializer):
    class Meta:
        model = User
        fields = ['firstName', 'lastName', 'email', 'password']
        extra_kwargs = {
            'password': {'write_only': True}
        }

    def create(self, validated_data):
        validated_data['password'] = make_password(validated_data['password'])
        return super(UserSerializer, self).create(validated_data)

class SignInSerializer(serializers.Serializer):
    email = serializers.CharField()
    password = serializers.CharField()
