from django.urls import path
from . import views
from rest_framework.routers import DefaultRouter
from sensor.views import ContainerViewset, SensorViewset, UserViewset
from django.urls import include
router = DefaultRouter()
router.register(r'container', ContainerViewset)
router.register(r'sensor', SensorViewset)
router.register(r'user', UserViewset)
from rest_framework_simplejwt import views as JwtViews
from rest_framework_simplejwt.views import TokenRefreshView

urlpatterns = [
    path(r'', include(router.urls)),
    path("sensor_list/", views.SensorList.as_view(), name="sensor_list"),
    path(
        "sensor_detail/<uuid:pk>/", views.SensorDetail.as_view(), name="sensor_detail"
    ),
    path("user_detail/<uuid:pk>/", views.UserDetail.as_view(), name="user_detail"),
    path(
        "container_detail/<uuid:pk>/",
        views.ContainerDetail.as_view(),
        name="container_detail",
    ),
    path("test_connection/", views.test_connection, name="test_connection"),
    path(
        "user_list/",
        views.UserList.as_view(),
        name="user_list",
    ),
    path("container_list/", views.ContainerList.as_view(), name="container_list"),
    path(
        "container_location/",
        views.ContainerLocation.as_view(),
        name="container_location",
    ),
    path("signUp/", views.RegisterView.as_view()),
    path('signIn/', views.MyObtainTokenPairView.as_view()),
    path('signIn/refresh/', TokenRefreshView.as_view()),
    # path("signInWebJwt/", JwtViews.token_obtain_pair.as_view()),
]
