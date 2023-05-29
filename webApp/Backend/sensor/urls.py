from django.urls import path
from . import views

urlpatterns = [
    path("signUp/", views.signUp),
    path("signIn/", views.signIn),
    path("signOut/", views.signOut),
    path("signedInUser/", views.signedInUser)
]
