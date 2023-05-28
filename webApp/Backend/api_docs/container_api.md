# Container API

Using the Container API, one can access the container data stored in the database. All container data is constructed with six columns per table entry. These are

- container_content: The contents of the container as String.
- container_start: The starting location of the container as String.
- container_destination: The destination of the container as String.
- container_time: The datetime object the container was created
-  container_id: A UUID that distinquishes the container data entry from the rest (primary key).
- container_door_closed: A boolean value that indicates whether the door was closed or not.

A container data entry returns their contents based on the provided API endpoint in JSON format. 

## ContainerList - `api/container_list/` - GET

> List all container data, or create a new container data list

This view can be accessed using this statement:

```js
const containerListResponse = await fetch("http://127.0.0.1:8000/api/container_list");
```

A container data entry returns their contents based on the provided API endpoint in JSON format. 

## ContainerDetail - `api/container_detail/<uuid:id>/` - GET

> Retrieve, update or delete a container data instance

A container data entry can be retrieved, updated or deleted from within the API by calling the ContainerDetail view. 

```js
const containerDetailResponse = await fetch("http://127.0.0.1:8000/api/container_detail/<uuid:id>/");
```

## ContainerLocation - `api/container_location/` - POST

> Find the current Location of a container based on its last posted coordinates

This API endpoint provides the current location of a container based on its last posted coordinates. The API endpoint requires a POST request with the container id as a parameter.


```js
async function fetchLocationOfContainer(id){
const containerLocationResponse = await fetch("http://127.0.0.1:8000/api/container_location/", {
    method: "POST",
    headers: {
        "Content-Type": "application/json",
    },
    body: JSON.stringify({
        "id": id,
    }),
})};

```


## ContainerByContent - `api/container_by_content/` - POST

> Get all containers with a certain content


This API endpoint provides all containers with a certain content. The API endpoint requires a POST request with the container content as a parameter.

```js
async function fetchLocationOfContainer(content){
const containerLocationResponse = await fetch("http://127.0.0.1:8000/api/container_location/", {
    method: "POST",
    headers: {
        "Content-Type": "application/json",
    },
    body: JSON.stringify({
        "content": content,
    }),
})};
```

