import json
from django.http import HttpResponse, JsonResponse
from django.views.decorators.csrf import csrf_exempt
from rest_framework.parsers import JSONParser
from .models import SensorData, User
from .serializer import SensorSerializer, SignInSerializer, UserSerializer

from django.contrib.auth.decorators import login_required
from django.contrib.auth import authenticate, login, logout

# Create your views here.
"""
Retrieve a single sensor info from db
"""
@csrf_exempt
def sensor_detail(request, pk):
    try:
        sensor = SensorData.objects.get(pk=pk)
    except SensorData.DoesNotExist:
        return HttpResponse(status=404)

    if request.method == 'GET':
        serializer = SensorSerializer(sensor)
        return JsonResponse(serializer.data)

    elif request.method == 'PUT':
        data = JSONParser().parse(request)
        serializer = SensorSerializer(sensor, data=data)
        if serializer.is_valid():
            serializer.save()
            return JsonResponse(serializer.data)
        return JsonResponse(serializer.errors, status=400)

    elif request.method == 'DELETE':
        sensor.delete()
        return HttpResponse(status=204)
    
class ResponseModel:
    def __init__(self, errorMsg = "", data = ""):
        self.errorMsg = errorMsg
        self.data = data


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
        user = authenticate(request, username=serializer.data.get('email', None), password=serializer.data.get('password', None))
        if user is not None:
            login(request, user)
            return JsonResponse({'email': serializer.data['email']})
        else:
            responseObj = ResponseModel()
            responseObj.errorMsg = "Sorry but there is a mismatch with your credentials."
            return JsonResponse(responseObj.__dict__, status=400)

    return JsonResponse(serializer.errors, status=400)

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