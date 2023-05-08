from django.http import HttpResponse, JsonResponse
from django.views.decorators.csrf import csrf_exempt
from rest_framework.parsers import JSONParser
from .models import SensorData
from .serializer import SensorSerializer

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
    

def signOut(request, userUuid):
    return HttpResponse("You want me to sign out the user with id:  %s." % userUuid)
