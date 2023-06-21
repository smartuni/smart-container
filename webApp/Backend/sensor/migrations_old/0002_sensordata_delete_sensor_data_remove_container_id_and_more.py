# Generated by Django 4.1.7 on 2023-05-14 16:30

from django.db import migrations, models
import django.db.models.deletion
import uuid


class Migration(migrations.Migration):
    dependencies = [
        ("sensor", "0001_initial"),
    ]

    operations = [
        migrations.CreateModel(
            name="SensorData",
            fields=[
                (
                    "id",
                    models.UUIDField(
                        default=uuid.uuid4,
                        editable=False,
                        primary_key=True,
                        serialize=False,
                    ),
                ),
                ("sensor_type", models.CharField(max_length=10)),
                ("sensor_data", models.CharField(max_length=100)),
                ("sensor_time", models.DateTimeField()),
            ],
            options={
                "ordering": ["sensor_time"],
            },
        ),
        migrations.RemoveField(
            model_name="container",
            name="id",
        ),
        migrations.RemoveField(
            model_name="user",
            name="id",
        ),
        migrations.AddField(
            model_name="container",
            name="container_id",
            field=models.UUIDField(
                default=uuid.uuid4, editable=False, primary_key=True, serialize=False
            ),
        ),
        migrations.AddField(
            model_name="user",
            name="user_id",
            field=models.UUIDField(
                default=uuid.uuid4, editable=False, primary_key=True, serialize=False
            ),
        ),
        migrations.AddField(
            model_name="sensordata",
            name="owner",
            field=models.ForeignKey(
                on_delete=django.db.models.deletion.CASCADE,
                related_name="sensor_data",
                to="sensor.container",
            ),
        ),
    ]