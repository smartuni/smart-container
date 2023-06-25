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
    path("test_connection/", views.test_connection, name="test_connection"),
    path("signUp/", views.RegisterView.as_view()),
    path('signIn/', views.MyObtainTokenPairView.as_view()),
    path('signIn/refresh/', TokenRefreshView.as_view()),
    path("container_location/", views.ContainerLocation.as_view())
    # path("signInWebJwt/", JwtViews.token_obtain_pair.as_view()),
]
