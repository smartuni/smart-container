# Sensor API

Using the Sensor API, one can access the sensor data stored in the database. All sensor data is constructed with five columns per table entry. These are

- sensor_data: The data stored in the sensorData row as String.
- sensor_time: The datetime object of when the data was captured
- sensor_type: The unit or type of sensor data recorded (e.g. temperature) as String
- owner: The container to which the sensor data entry belongs to (foreign key, many-to-one) as UUID
- id: The UUID key that distinquishes the sensor data entry from the rest (primary key).

A sensor data entry returns their contents based on the provided API endpoint in JSON format. 

## SensorList

> List all sensor data

This view can be accessed using this statement:

```js
const sensorListResponse = await fetch("http://127.0.0.1:8000/sensor_list");
```

A sensor list can be viewed using get.

An example of the output:

## SensorDetail

>  Retrieve, update or delete a sensor data instance


A sensor data entry can be retrieved, updated or deleted from within the API by calling the SensorDetail view. 

```js
const sensorDetailResponse = await fetch("http://127.0.0.1:8000/sensor_detail/<uuid:id>/");
```
or using requestOptions (recommended):
```js
const sensorDetailRequestOptions = {
    method: 'GET',
    credentials: 'include' as RequestCredentials,
    mode: 'cors' as RequestMode,
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ id: sensorID }),
}

const sensorDetailResponse = await fetch("http://127.0.0.1:8000/sensor_detail/", sensorDetailRequestOptions);
```

A sensor detail contains just the information of the single sensor data instance recorded from the database. For our case, viewing sensor data using GET is the most interesting case.

An example output of a GET request to this API:
