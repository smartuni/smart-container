from rest_framework import serializers
from .models import Sensor_Data
    
class SensorSerializer(serializers.ModelSerializer):
    class Meta:
        model = Sensor_Data
        fields = ['id', 'sensor_type', 'sensor_data', 'sensor_time']

