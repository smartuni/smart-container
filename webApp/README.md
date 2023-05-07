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
- Humidity
- Acceleration (status of the node (crashed?))
- Wather leak
- Door sensor
- NFC-tag (get content of container listed, Authentication)

## Data model (Api response type: JSON)

```json
{
  "Container": [
    { 
      "id": "UUID", 
      "start": "string", 
      "dest": "string", 
      "door_status": "boolean", 
      "content": "string", 
      "userId": "UUID", 
      "crashed": "boolean",
      "threshold": {
        "string": {
          "min": "string",
          "max": "string",
        }
      }
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
     "id" : "UUID",
     "data_type": "string",
     "value": "string",
     "datetime": "string",
     "container_id": "UUID"
   }
  ]
}
```
