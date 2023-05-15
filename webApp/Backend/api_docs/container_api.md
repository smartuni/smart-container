# Container API

Using the Container API, one can access the container data stored in the database. All container data is constructed with six columns per table entry. These are

- container_content: The contents of the container as String.
- container_start: The starting location of the container as String.
- container_destination: The destination of the container as String.
- container_time: The datetime object the container was created
-  container_id: A UUID that distinquishes the container data entry from the rest (primary key).
- container_door_closed: A boolean value that indicates whether the door was closed or not.

A container data entry returns their contents based on the provided API endpoint in JSON format. 

## ContainerList

> List all container data, or create a new container data list

This view can be accessed using this statement:

```js
const containerListResponse = await fetch("http://

A container data entry returns their contents based on the provided API endpoint in JSON format. 
