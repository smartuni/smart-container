
/*
Sensor node code which reads a sensor periodacly or event based and sends the data to the concentrator node via coap
*/


//include 
#include "coap_code.h"
#include "sensor_code.h"

// declare functions
static size_t discover_concentrator(void);

// start main function
int main(void)
{
    discover_concentrator();

    puts("Get sensor value");

    sensor_value = read_sensor();

    //printf("\nSend msg with payload %d\n", sensorReading);
    
    return 0;
}


static size_t discover_concentrator(void){
// function discovers concentrator node and saves the path where to post the sensor data    

    // call multicast address via COAP_GET
    if (!send_req("ff02::1", "5683", "/.well-known/core", "0", COAP_GET)) {//ff02::1 //fe80::fcb2:9130:a6fa:74b3
        puts("multicast send");
    } else
    puts("multicast failed");

    return 0;
}