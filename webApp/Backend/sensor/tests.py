import datetime
import uuid
from django.urls import reverse
from rest_framework.routers import DefaultRouter
from rest_framework import status
from rest_framework.test import APITestCase, URLPatternsTestCase
from django.urls import include, path

from .models import Container, SensorData, User
from sensor.serializer import ContainerSerializer, SensorSerializer, UserSerializer

test_id = uuid.uuid4()
test_date = datetime.datetime.now()
test_container = Container.objects.create(container_id=uuid.uuid4(), container_start="Berlin", container_destination="Hamburg", container_content="Bananas", container_door_closed=True, container_time=test_date)
router = DefaultRouter()

class ContainerViewSetTests(APITestCase, URLPatternsTestCase):
    urlpatterns = [
        path('', include(router.urls)),
    ]

    def setUp(self):
        self.container = Container.objects.create(container_id=uuid.uuid4(), container_start="Berlin", container_destination="Hamburg", container_content="Bananas", container_door_closed=True, container_time=datetime.datetime.now())

    def test_list_containers(self):
        """
        Ensure we can list all containers
        """
        url = reverse('container-list')
        response = self.client.get(url)
        data = response.json()
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        containers = Container.objects.all()
        serializer = ContainerSerializer(containers, many=True)
        self.assertEqual(data, serializer.data)

    def test_retrieve_container(self):
        """
        Ensure we can retrieve a single container
        """
        url = reverse('container-detail', args=[self.container.container_id])
        response = self.client.get(url)
        data = response.json()
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        serializer = ContainerSerializer(self.container)
        self.assertEqual(data, serializer.data)

    def test_create_container(self):
        """
        Ensure we can create a new container
        """
        url = reverse('container-list')
        data = {
            'container_id': uuid.uuid4(),
            'container_start': 'Berlin',
            'container_destination': 'Hamburg',
            'container_content': 'Apples',
            'container_door_closed': True,
            'container_time': datetime.datetime.now()
        }
        response = self.client.post(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_201_CREATED)
        container = Container.objects.get(container_id=data['container_id'])
        serializer = ContainerSerializer(container)
        self.assertEqual(response.json(), serializer.data)

    def test_update_container(self):
        """
        Ensure we can update an existing container
        """
        url = reverse('container-detail', args=[self.container.id])
        data = {
            'container_content': 'Oranges',
            'container_door_closed': False
        }
        response = self.client.patch(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        self.container.refresh_from_db()
        self.assertEqual(self.container.container_content, data['container_content'])
        self.assertEqual(self.container.container_door_closed, data['container_door_closed'])

    def test_delete_container(self):
        """
        Ensure we can delete an existing container
        """
        url = reverse('container-detail', args=[self.container.id])
        response = self.client.delete(url)
        self.assertEqual(response.status_code, status.HTTP_204_NO_CONTENT)
        self.assertFalse(Container.objects.filter(id=self.container.id).exists())




class SensorDetailTests(APITestCase):
    def test_retrieve_sensor(self):
        """
        Ensure we can retrieve a sensor data instance
        """
        test_container = Container.objects.create(container_id=uuid.uuid4(), container_start="Berlin", container_destination="Hamburg", container_content="Bananas", container_door_closed=True, container_time=test_date)
        sensor = SensorData.objects.create(id=test_id, sensor_time=test_date, sensor_data="42", owner=test_container, sensor_type="GPS")
        url = reverse('sensor_detail', args=[sensor.id])
        response = self.client.get(url)
        data = response.json()
        print(data)
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        serializer = SensorSerializer(sensor)
        self.assertEqual(data['sensor_data'], serializer.data['sensor_data'])

    def test_update_sensor(self):
        """
        Ensure we can update a sensor data instance
        """
        test_container = Container.objects.create(container_id=uuid.uuid4(), container_start="Berlin", container_destination="Hamburg", container_content="Bananas", container_door_closed=True, container_time=test_date)
        sensor = SensorData.objects.create(id=test_id, sensor_time=test_date, sensor_data="42", owner=test_container, sensor_type="GPS")
        url = reverse('sensor_detail', args=[sensor.id])
        data = {"id": test_id, "sensor_time": test_date, "sensor_data": "86", "owner": test_container, "sensor_type": "GPS"}
        response = self.client.put(url, data)
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        sensor.refresh_from_db()
        self.assertEqual(sensor.sensor_data, "86")

#     def test_delete_sensor(self):
#         """
#         Ensure we can delete a sensor data instance
#         """
#         sensor = SensorData.objects.create(name='Test Sensor', value=42)
#         url = reverse('sensor-detail', args=[sensor.id])
#         response = self.client.delete(url)
#         self.assertEqual(response.status_code, status.HTTP_204_NO_CONTENT)
#         self.assertFalse(SensorData.objects.filter(id=sensor.id).exists())


# class UserListTests(APITestCase):
#     def test_list_users(self):
#         """
#         Ensure we can list all user data
#         """
#         url = reverse('user-list')
#         response = self.client.get(url)
#         self.assertEqual(response.status_code, status.HTTP_200_OK)
#         users = User.objects.all()
#         serializer = UserSerializer(users, many=True)
#         self.assertEqual(response.data, serializer.data)


# class UserDetailTests(APITestCase):
#     def test_retrieve_user(self):
#         """
#         Ensure we can retrieve a user data instance
#         """
#         user = User.objects.create(username='testuser')
#         url = reverse('user-detail', args=[user.id])
#         response = self.client.get(url)
#         self.assertEqual(response.status_code, status.HTTP_200_OK)
#         serializer = UserSerializer(user)
#         self.assertEqual(response.data, serializer.data)

#     def test_update_user(self):
#         """
#         Ensure we can update a user data instance
#         """
#         user = User.objects.create(username='testuser')
#         url = reverse('user-detail', args=[user.id])
#         data = {'username': 'updateduser'}
#         response = self.client.put(url, data)
#         self.assertEqual(response.status_code, status.HTTP_200_OK)
#         user.refresh_from_db()
#         self.assertEqual(user.username, 'updateduser')

#     def test_delete_user(self):
#         """
#         Ensure we can delete a user data instance
#         """
#         user = User.objects.create(username='testuser')
#         url = reverse('user-detail', args=[user.id])
#         response = self.client.delete(url)
#         self.assertEqual(response.status_code, status.HTTP_204_NO_CONTENT)
#         self.assertFalse(User.objects.filter(id=user.id).exists())
