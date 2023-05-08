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
    
# TODO: Change the Response type to JSON
def signUp(request):
    try:
        user = User.objects.create_user("florian", "florian@haw.de", "123")
    except:
        return HttpResponse("The user seems to be already existing.")

    return HttpResponse("You are singed up as: %s", user)

def signIn(request):
    username = request.POST.get("username", "")
    password = request.POST.get("password", "")
    user = authenticate(request, username=username, password=password)

    if user is not None:
        login(request, user)
        return HttpResponse("You are logged in")
    else:
        return HttpResponse("Sorry but there is a mismatch with your credentials.")

@login_required
def signOut(request):
    logout(request)
    return HttpResponse("Successfully signed out.")

def checkSignedIn(request):
    if request.user.is_authenticated:
        return HttpResponse("You are currently signed in.")
    else:
        return HttpResponse("You are currently NOT signed in.")