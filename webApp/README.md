# RiotWebApp

## Team

Team Lead *Emily*

**Frontend**: Lead *Sahar*
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

## Data model

```json
[
  { 
    id : UUID,
    position: {
      GPS: {
        lat: float,
        long: float
      }, 
      time: DateTime
    },
    temperature: float,
    humidity: float,
    acceleration: boolean,
    door_sensor: boolean,
    nfc_tag: UserId
  }
]

