### COAP
- POST Sensor->Concentrator
    - Door-Sensor (event)
    - Impact-Sensor (event)
    - Waterleak-Sensor (event)
    - Temperature/Humidity-Sensor (periodically)    - 
    - GPS (periodically, maybe based on speed)

### SD-Card
save to sd-card on data arrival

### LoRaWAN
- periodically with constraint of data rate
- data rate adapted dynamically based on range to node
- sync protocoll when data rate is high enough to re-transmit data from out-of-range transmissions

### Ideas
- Battery Low (on-action) or battery state (periodically)     (probably not possible, speak again next week (21.04))
- 'Alive check' on event-based nodes. Send ping every x hours
    
