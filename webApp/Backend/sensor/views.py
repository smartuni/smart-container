from django.http import HttpResponse, JsonResponse
from django.views.decorators.csrf import csrf_exempt
from rest_framework.parsers import JSONParser
from .models import SensorData, Container, User
from .serializer import SensorSerializer, ContainerSerializer, UserSerializer
from rest_framework import generics
from rest_framework.views import APIView


from django.contrib.auth.models import User
from django.contrib.auth.decorators import login_required
from django.contrib.auth import authenticate, login, logout

# Create your views here.


class SensorList(generics.ListAPIView):
    """
    List all sensor data
    """

    queryset = SensorData.objects.all()
    serializer_class = SensorSerializer


class SensorDetail(generics.RetrieveUpdateDestroyAPIView):
    """
    Retrieve, update or delete a sensor data instance
    """

    queryset = SensorData.objects.all()
    serializer_class = SensorSerializer


class UserList(generics.ListAPIView):
    """
    List all user data
    """

    queryset = User.objects.all()
    serializer_class = UserSerializer


class UserDetail(generics.RetrieveUpdateDestroyAPIView):
    """
    Retrieve, update or delete a user data instance
    """

    queryset = User.objects.all()
    serializer_class = UserSerializer


class ContainerList(generics.ListAPIView):
    """
    List all container data
    """

    queryset = Container.objects.all()
    serializer_class = ContainerSerializer


class ContainerDetail(generics.RetrieveUpdateDestroyAPIView):
    """
    Retrieve, update or delete a container data instance
    """

    queryset = Container.objects.all()
    serializer_class = ContainerSerializer


class ContainerLocation(APIView):
    """
    Retrieve container location
    """

    def get(self, request, format=None):
        container = Container.objects.get(container_id=request.GET["container_id"])
        gpsLocation = SensorData.objects.filter(
            sensor_type="GPS", owner=container
        ).latest("sensor_time")
        serializer = SensorSerializer(gpsLocation)
        return JsonResponse(serializer.data, safe=False)
