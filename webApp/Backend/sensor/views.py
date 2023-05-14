from django.http import HttpResponse, JsonResponse
from django.views.decorators.csrf import csrf_exempt
from rest_framework.parsers import JSONParser
from .models import SensorData
from .serializer import SensorSerializer
from rest_framework import generics


# Create your views here.


class SensorList(generics.ListCreateAPIView):
    """
    List all sensor data, or create a new sensor data list
    """

    queryset = SensorData.objects.all()
    serializer_class = SensorSerializer
