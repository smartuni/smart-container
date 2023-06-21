#!/bin/bash

python manage.py makemigrations
python manage.py makemigrations sensor
python manage.py migrate

python manage.py shell < sensor/mqtt.py & 
gunicorn -b 0.0.0.0:8000 server.wsgi
#python manage.py shell < sensor/mqtt.py