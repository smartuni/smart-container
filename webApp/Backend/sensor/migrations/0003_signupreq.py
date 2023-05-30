# Generated by Django 4.2 on 2023-05-29 12:40

from django.db import migrations, models


class Migration(migrations.Migration):
    dependencies = [
        ("sensor", "0002_alter_sensordata_sensor_type"),
    ]

    operations = [
        migrations.CreateModel(
            name="SignUpReq",
            fields=[
                (
                    "id",
                    models.BigAutoField(
                        auto_created=True,
                        primary_key=True,
                        serialize=False,
                        verbose_name="ID",
                    ),
                ),
                ("firstName", models.CharField(max_length=256)),
                ("lastName", models.CharField(max_length=256)),
                ("email", models.CharField(max_length=256)),
                ("password", models.CharField(max_length=128)),
            ],
        ),
    ]
