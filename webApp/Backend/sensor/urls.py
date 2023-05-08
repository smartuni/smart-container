from django.urls import path
from . import views

urlpatterns = [
    # ex: /polls/5/
    path("<int:question_id>/", views.signOut, name="detail")
]
