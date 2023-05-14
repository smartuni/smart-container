from django.urls import path
from . import views

urlpatterns = [
    path("sensor_list/", views.SensorList.as_view(), name="sensor_list"),
]
