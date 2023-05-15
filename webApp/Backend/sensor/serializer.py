from rest_framework import serializers
from .models import SensorData
    
class SensorSerializer(serializers.ModelSerializer):
    class Meta:
        model = SensorData
        fields = ['id', 'data_type', 'value', 'datetime', 'container_id']

