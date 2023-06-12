import json
from django.contrib.auth.models import User
from django.contrib.auth import authenticate, login, logout
from django.contrib.auth.decorators import login_required
from django.http import HttpResponse, JsonResponse
from django.views.decorators.csrf import csrf_exempt
from rest_framework.mixins import (
    CreateModelMixin, ListModelMixin, RetrieveModelMixin, UpdateModelMixin, DestroyModelMixin
)
from rest_framework.viewsets import GenericViewSet
from rest_framework import generics, viewsets
from rest_framework.views import APIView
from .models import SensorData, Container, User
from .serializer import SensorSerializer, ContainerSerializer, UserSerializer

from rest_framework.parsers import JSONParser
from .models import SensorData, User
from .serializer import SensorSerializer, SignInSerializer, UserSerializer

from django.contrib.auth.decorators import login_required
from django.contrib.auth import authenticate, login, logout

# Create your views here.


class SensorViewset(viewsets.ModelViewSet):
    """
    List all sensor data
    """

    queryset = SensorData.objects.all()
    serializer_class = SensorSerializer


# class SensorDetail(CreateModelMixin, # handles CREATEs for 1 Sensor
#                      GenericViewSet,  # generic view functionality
#                      RetrieveModelMixin,  # handles GETs for 1 Sensor
#                      UpdateModelMixin,  # handles PUTs and PATCHes
#                      ListModelMixin,    # handles GETs for many Sensors
#                      DestroyModelMixin):  #handles DELETEs for 1 Sensor
#     """
#     Create, Retrieve, update or delete a sensor data instance
#     """

#     queryset = SensorData.objects.all()
#     serializer_class = SensorSerializer

#     # Specify the allowed actions and their corresponding HTTP methods
#     action_map = {
#         'get': 'retrieve',
#         'put': 'update',
#         'patch': 'partial_update',
#         'delete': 'destroy',
#         'post': 'create',
#         'list': 'list',
#     }

#     @classmethod
#     def get_action_map(cls):
#         return cls.action_map

#     # Override the `as_view` method to provide the `actions` argument
#     @classmethod
#     def as_view(cls, actions=None, **initkwargs):
#         actions = actions or cls.get_action_map()
#         return super().as_view(actions=actions, **initkwargs)

class UserViewset(viewsets.ModelViewSet):
    """
    List all container data
    """

    queryset = User.objects.all()
    serializer_class = UserSerializer


# class UserDetail(CreateModelMixin, # handles CREATEs for 1 User
#                     GenericViewSet,  # generic view functionality
#                      RetrieveModelMixin,  # handles GETs for 1 User
#                      UpdateModelMixin,  # handles PUTs and PATCHes
#                      ListModelMixin,    # handles GETs for many Users
#                      DestroyModelMixin):  #handles DELETEs for 1 User
#     """
#     Retrieve, update or delete a user data instance
#     """

#     queryset = User.objects.all()
#     serializer_class = UserSerializer

#         # Specify the allowed actions and their corresponding HTTP methods
#     action_map = {
#         'get': 'retrieve',
#         'put': 'update',
#         'patch': 'partial_update',
#         'delete': 'destroy',
#         'post': 'create',
#         'list': 'list',
#     }

#     @classmethod
#     def get_action_map(cls):
#         return cls.action_map

#     # Override the `as_view` method to provide the `actions` argument
#     @classmethod
#     def as_view(cls, actions=None, **initkwargs):
#         actions = actions or cls.get_action_map()
#         return super().as_view(actions=actions, **initkwargs)

class ContainerViewset(viewsets.ModelViewSet):
    """
    List all container data
    """

    queryset = Container.objects.all()
    serializer_class = ContainerSerializer


# class ContainerDetail(CreateModelMixin, # handles CREATEs for 1 Container
#                     GenericViewSet,  # generic view functionality
#                      RetrieveModelMixin,  # handles GETs for 1 Container
#                      UpdateModelMixin,  # handles PUTs and PATCHes
#                      ListModelMixin,    # handles GETs for many Containers
#                      DestroyModelMixin):  #handles DELETEs for 1 Container

#     """
#     Retrieve, update or delete a container data instance
#     """
#     queryset = Container.objects.all()
#     serializer_class = ContainerSerializer

#         # Specify the allowed actions and their corresponding HTTP methods
#     action_map = {
#         'get': 'retrieve',
#         'put': 'update',
#         'patch': 'partial_update',
#         'delete': 'destroy',
#         'post': 'create',
#         'list': 'list',
#     }

#     @classmethod
#     def get_action_map(cls):
#         return cls.action_map

#     # Override the `as_view` method to provide the `actions` argument
#     @classmethod
#     def as_view(cls, actions=None, **initkwargs):
#         actions = actions or cls.get_action_map()
#         return super().as_view(actions=actions, **initkwargs)

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


@csrf_exempt
def signUp(request):
    try:
        data = JSONParser().parse(request)
    except:
        responseObj = ResponseModel()
        responseObj.errorMsg = "Missing valid JSON in body."
        return JsonResponse(responseObj.__dict__, status=400)

    serializer = UserSerializer(data=data)

    if serializer.is_valid():
        serializer.save()
        return JsonResponse(serializer.data)

    return JsonResponse(serializer.errors, status=400)


@csrf_exempt
def signIn(request):
    try:
        data = JSONParser().parse(request)
    except:
        responseObj = ResponseModel()
        responseObj.errorMsg = "Missing valid JSON in body."
        return JsonResponse(responseObj.__dict__, status=400)

    serializer = SignInSerializer(data=data)

    if serializer.is_valid():
        user = authenticate(
            request,
            username=serializer.data.get("email", None),
            password=serializer.data.get("password", None),
        )
        if user is not None:
            login(request, user)
            return JsonResponse({"email": serializer.data["email"]})
        else:
            responseObj = ResponseModel()
            responseObj.errorMsg = (
                "Sorry but there is a mismatch with your credentials."
            )
            return JsonResponse(responseObj.__dict__, status=400)

    return JsonResponse(serializer.errors, status=400)


class ResponseModel:
    def __init__(self, errorMsg="", data=""):
        self.errorMsg = errorMsg
        self.data = data



@csrf_exempt
def signOut(request):
    logout(request)

    responseObj = ResponseModel()
    responseObj.data = "Successfully signed out."
    return JsonResponse(responseObj.__dict__)


# * Testing
@csrf_exempt
def signedInUser(request):
    responseObj = ResponseModel()

    if request.user.is_authenticated:
        responseObj.data = f"You are currently signed is as {request.user}."
    else:
        responseObj.errorMsg = "You are currently NOT signed in."

    return JsonResponse(responseObj.__dict__)
