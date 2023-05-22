
/*
Sensor node code which reads a sensor periodacly or event based and sends the data to the concentrator node via coap
*/


//include 
#include "coap_code.h"
#include "temperature_code.h"

//#include "humidity_code.h"

// declare functions
static size_t discover_concentrator(void);

//declare variables
#define LENGTH 10
char sensor_value[LENGTH];


// start main function
int main(void)
{
    if (discover_concentrator()){
        puts("sending multicast failed, ending program!");
        return 0;
    }

    // intitialize timer
    ztimer_now_t last_wakeup = ztimer_now(ZTIMER_MSEC);

    while(1) {
        puts("Get sensor value");

        read_sensor(sensor_value, LENGTH);
       
        printf("Wert: %s\n", sensor_value);
        send_req("fe80::fcb2:9130:a6fa:74b3", "5683", coap_path, sensor_value, COAP_POST);

        ztimer_periodic_wakeup(ZTIMER_MSEC, &last_wakeup, 10000);
    }
    
    return 0;
}


static size_t discover_concentrator(void){
// function discovers concentrator node and saves the path where to post the sensor data    

    puts("Send multicast to discover concentrator");
    // call multicast address via COAP_GET
    if (!send_req("fe80::fcb2:9130:a6fa:74b3", "5683", "/.well-known/core", "0", COAP_GET)) {//ff02::1 //fe80::fcb2:9130:a6fa:74b3
        puts("multicast send");
    } else {
        puts("multicast failed");
        return 1;
    }
    return 0;
}