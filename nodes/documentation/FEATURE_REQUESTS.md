### COAP
- POST
    - Battery Low (SENSOR->CONCENTRATOR)(on-action)
    - Door-Sensor (SENSOR->CONCENTRATOR)(on-action)
    - Impact-Sensor (SENSOR->CONCENTRATOR)(on-action)
    - Waterleak-Sensor (SENSOR->CONCENTRATOR)(on-action)
    - Temperature/Humidity-Sensor (SENSOR->CONCENTRATOR)(periodically)    - 
- GET
    - Health Check (CONCENTRATOR->SENSOR)(periodically)
    - GPS (CONCENTRATOR->SENSOR)(on-sensor-post-event)

### SD-Card
save to sd-card on data arrival

### LoRaWAN
- periodically with constraint of data rate
- data rate adapted dynamically based on range to node
- sync protocoll when data rate is high enough to re-transmit data from out-of-range transmissions