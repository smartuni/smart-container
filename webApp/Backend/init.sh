#!/bin/bash

python manage.py makemigrations
python manage.py migrate
gunicorn -b 0.0.0.0:8000 server.wsgi
