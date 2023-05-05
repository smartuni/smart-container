from django.http import HttpResponse, JsonResponse
from django.views.decorators.csrf import csrf_exempt
from rest_framework.parsers import JSONParser
from .models import Sensor_Data
from .serializer import SensorSerializer

# Create your views here.


@csrf_exempt
def sensor_data(request, pk):
    """
    Retrieve a single sensor info from db
    """
    try:
        sensor = Sensor_Data.objects.get(pk=pk)
    except Sensor_Data.DoesNotExist:
        return HttpResponse(status=404)

    if request.method == "GET":
        serializer = SensorSerializer(sensor)
        return JsonResponse(serializer.data)

    elif request.method == "PUT":
        data = JSONParser().parse(request)
        serializer = SensorSerializer(sensor, data=data)
        if serializer.is_valid():
            serializer.save()
            return JsonResponse(serializer.data)
        return JsonResponse(serializer.errors, status=400)

    elif request.method == "DELETE":
        sensor.delete()
        return HttpResponse(status=204)


def all_sensor_data(request):
    """
    List all sensor info from db
    """
    if request.method == "GET":
        sensor = Sensor_Data.objects.all()
        serializer = SensorSerializer(sensor, many=True)
        return JsonResponse(serializer.data, safe=False)

    elif request.method == "POST":
        data = JSONParser().parse(request)
        serializer = SensorSerializer(data=data)
        if serializer.is_valid():
            serializer.save()
            return JsonResponse(serializer.data, status=201)
        return JsonResponse(serializer.errors, status=400)


def sensor_data_by_type(request, sensor_type):
    """
    Gets all sensor data by sensor data type
    """
    if request.method == "GET":
        sensor = Sensor_Data.objects.filter(sensor_type=sensor_type)
        serializer = SensorSerializer(sensor, many=True)
        return JsonResponse(serializer.data, safe=False)

    return HttpResponse(status=400)


def sensor_data_by_location(request, location):
    if request.method == "GET":
        sensor = Sensor_Data.objects.filter(location=location)
        serializer = SensorSerializer(sensor, many=True)
        return JsonResponse(serializer.data, safe=False)

    return HttpResponse(status=400)


def sensor_data_by_container(request, container_id):
    if request.method == "GET":
        sensor = Sensor_Data.objects.filter(container_id=container_id)
        serializer = SensorSerializer(sensor, many=True)
        return JsonResponse(serializer.data, safe=False)

    return HttpResponse(status=400)
