# RiotWebApp

## Team

Team Lead *Emily*

**Frontend**: Lead *Alicia*
- Alicia
- Hamid
- Landon
- Sahar

**Backend**: Lead *Emily*
- David
- Emily
- Hilary
- Florian

## TecStack

**Frontend**:
- Next.js

**Backend**:
- Django (Python)
- Postgresql

## What we do

We are responsible for displaying collected data from distributed nodes.
- Position (GPS, Time)
- Temperature
- Humanity
- Acceleration (status of the node (crashed?))
- Door sensor
- NFC-tag (get content of container listed, Authentication)

## Data model (Api response type: JSON)

```json
{
  "Container": [
    { 
      "id": "string", 
      "start": "string", 
      "dest": "string", 
      "door_status": "boolean", 
      "content": "string", 
      "userId": "string", 
      "crashed": "boolean"
    },
  ],
  "User": [
   { 
     "id" : "UUID",
     "firstName": "string",
     "lastName": "string",
     "email": "string",
     "password": "string",
     "company": "string",
     "role": "string",
   }
  ],
  "SensorData": [
   { 
     "id" : "integer",
     "data_type": "string",
     "value": "string",
     "datetime": "string",
     "container_id": "integer"
   }
  ]
}
```
