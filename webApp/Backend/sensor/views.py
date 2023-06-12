import json
from django.contrib.auth.models import User
from django.contrib.auth import authenticate, login, logout
from django.contrib.auth.decorators import login_required
from django.http import HttpResponse, JsonResponse
from django.views.decorators.csrf import csrf_exempt
from rest_framework import generics
from rest_framework.views import APIView
from .models import SensorData, Container, User
from .serializer import SensorSerializer, ContainerSerializer, UserSerializer

from rest_framework.parsers import JSONParser
from .models import SensorData, User
from .serializer import SensorSerializer, SignInSerializer, UserSerializer

from django.contrib.auth.decorators import login_required
from django.contrib.auth import authenticate, login, logout

from .serializer import MyTokenObtainPairSerializer, RegisterSerializer
from rest_framework.permissions import AllowAny
from rest_framework_simplejwt.views import TokenObtainPairView
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

    def post(self, request):
        """
        Return the latest GPS sensor data for a container
        """
        container = Container.objects.get(container_id=request.data["id"])
        gpsLocation = SensorData.objects.filter(
            sensor_type="GPS", owner=container
        ).latest("sensor_time")
        serializer = SensorSerializer(gpsLocation, many=False)
        return JsonResponse(serializer.data["sensor_data"], safe=False)


class SensorByType(APIView):
    """
    Retrieve sensor data by type and/or container
    """

    def post(self, request):
        """
        Return the sensor data by type and/or container
        """
        if request.data["id"] is None:
            sensorData = SensorData.objects.filter(sensor_type=request.data["type"])
        else:
            container = Container.objects.get(container_id=request.data["id"])
            sensorData = SensorData.objects.filter(
                sensor_type=request.data["type"], owner=container
            )
        serializer = SensorSerializer(sensorData, many=False)
        return JsonResponse(serializer.data["sensor_data"], safe=False)


class ContainerByContent(APIView):
    """
    Retrieve container data by content
    """

    def post(self, request):
        """
        Return the container data by content
        """
        containerData = Container.objects.filter(
            container_content=request.data["content"]
        )
        serializer = ContainerSerializer(containerData, many=False)
        return JsonResponse(serializer.data["container_id"], safe=False)


class MyObtainTokenPairView(TokenObtainPairView):
    permission_classes = (AllowAny,)
    serializer_class = MyTokenObtainPairSerializer

class RegisterView(generics.CreateAPIView):
    queryset = User.objects.all()
    permission_classes = (AllowAny,)
    serializer_class = RegisterSerializer