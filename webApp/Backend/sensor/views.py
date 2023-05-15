import json
from django.http import HttpResponse, JsonResponse
from django.views.decorators.csrf import csrf_exempt
from rest_framework.parsers import JSONParser
from .models import SensorData
from .serializer import SensorSerializer

from django.contrib.auth.models import User
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
    userSignUpObj = json.loads(request.body or "{}")
    responseObj = ResponseModel()

    username = userSignUpObj['username'] or None
    email = userSignUpObj['email'] or None
    password = userSignUpObj['password'] or None

    if username == None or not(1 <= len(username) <= 128): 
        responseObj.errorMsg = "Username has to be a String with length of 1 - 128 characters."
        return HttpResponse(json.dumps(responseObj.__dict__))
    if email == None or not(5 <= len(email) <= 128) or not "@" in email: 
        responseObj.errorMsg = "Email has to be a String with length of 5 - 128 characters and containing '@'."
        return HttpResponse(json.dumps(responseObj.__dict__))
    if password == None or not(8 <= len(password) <= 128): 
        responseObj.errorMsg = "Password has to be a String with length of 8 - 128 characters."
        return HttpResponse(json.dumps(responseObj.__dict__))

    try:
        user = User.objects.create_user(username, email, password)
    except:
        responseObj.errorMsg = "The user seems to be already exists."
        return HttpResponse(json.dumps(responseObj.__dict__))

    responseObj.data = f"You are singed up as: {user}"
    return HttpResponse(json.dumps(responseObj.__dict__))

@csrf_exempt
def signIn(request):
    userSignInObj = json.loads(request.body or "{}")
    responseObj = ResponseModel()

    username = userSignInObj['username'] or None
    password = userSignInObj['password'] or None

    if username == None or not(1 <= len(username) <= 128): 
        responseObj.errorMsg = "Username has to be a String with length of 1 - 128 characters."
        return HttpResponse(json.dumps(responseObj.__dict__))
    if password == None or not(8 <= len(password) <= 128): 
        responseObj.errorMsg = "Password has to be a String with length of 8 - 128 characters."
        return HttpResponse(json.dumps(responseObj.__dict__))

    user = authenticate(request, username=username, password=password)

    if user is not None:
        login(request, user)
        responseObj.data = "You are logged in"
        return HttpResponse(json.dumps(responseObj.__dict__))
    else:
        responseObj.errorMsg = "Sorry but there is a mismatch with your credentials."
        return HttpResponse(json.dumps(responseObj.__dict__))

@csrf_exempt
@login_required
def signOut(request):
    responseObj = ResponseModel()

    logout(request)

    responseObj.data = "Successfully signed out."
    return HttpResponse(json.dumps(responseObj.__dict__))

# TODO: Change the Response type to JSON
@csrf_exempt
def checkSignedIn(request):
    if request.user.is_authenticated:
        return HttpResponse("You are currently signed in.")
    else:
        return HttpResponse("You are currently NOT signed in.")