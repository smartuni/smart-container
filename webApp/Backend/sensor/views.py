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
def signUp(request):
    userSignUpObj = json.loads(request.body or "{}")
    responseObj = ResponseModel()

    username = userSignUpObj["username"] or None
    email = userSignUpObj["email"] or None
    password = userSignUpObj["password"] or None

    if username == None or not (1 <= len(username) <= 128):
        responseObj.errorMsg = (
            "Username has to be a String with length of 1 - 128 characters."
        )
        return HttpResponse(json.dumps(responseObj.__dict__))
    if email == None or not (5 <= len(email) <= 128) or not "@" in email:
        responseObj.errorMsg = "Email has to be a String with length of 5 - 128 characters and containing '@'."
        return HttpResponse(json.dumps(responseObj.__dict__))
    if password == None or not (8 <= len(password) <= 128):
        responseObj.errorMsg = (
            "Password has to be a String with length of 8 - 128 characters."
        )
        return HttpResponse(json.dumps(responseObj.__dict__))

    try:
        user = User.objects.create_user(username, email, password)
    except:
        responseObj.errorMsg = "The user seems to be already exists."
        return HttpResponse(json.dumps(responseObj.__dict__))

    responseObj.data = f"You are singed up as: {user}"
    return HttpResponse(json.dumps(responseObj.__dict__))


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
