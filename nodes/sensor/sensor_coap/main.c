
/*
Sensor node code which reads a sensor periodacly or event based and sends the data to the concentrator node via coap
*/


//include 
#include "coap_code.h"
#include "temperature_code.h"

// declare functions
static size_t discover_concentrator(void);

//declare variables
#define LENGTH 10
char sensor_value[LENGTH];
char concentrator_ip[IPV6_ADDR_MAX_STR_LEN];

// start main function
int main(void)
{   
    // intitialize timer
    ztimer_now_t last_wakeup = ztimer_now(ZTIMER_MSEC);

    // discover concentrator node via coap multicast
    discover_concentrator();    

    // periodically read and send sensor data
    while(1) {
        puts("Get sensor value\n");

        read_sensor(sensor_value, LENGTH);
       
        send_req(concentrator_ip, "5683", coap_path, sensor_value, COAP_POST, _resp_handler);

        ztimer_periodic_wakeup(ZTIMER_MSEC, &last_wakeup, 10000);
    }
    
    return 0;
}


static size_t discover_concentrator(void){
// function discovers concentrator node and saves its ip    

    ztimer_now_t last_wakeup = ztimer_now(ZTIMER_MSEC);

    puts("Send multicast to discover concentrator");

    // call multicast address via COAP_GET
    if (!send_req("ff02::1", "5683", "/.well-known/core", "0", COAP_GET, _discover_resp_handler)) {//ff02::1 //fe80::fcb2:9130:a6fa:74b3
        puts("multicast send, waiting for response");
    } else {
        puts("multicast failed");
        return 1;
    }
    while(1) {
        puts("Send multicast to discover concentrator");
        // call multicast address via COAP_GET
        if (!send_req("ff02::1", "5683", "/.well-known/core", "0", COAP_GET, _discover_resp_handler)) {//ff02::1 //fe80::fcb2:9130:a6fa:74b3
            puts("multicast send, waiting for response");

        } else {
            puts("multicast failed");
            coap_response = true;
        }
        while(!found_concentrator && !coap_response)                        // has to be changed, quick and dirty at the moment
        coap_response = false;

        if(found_concentrator){
            printf("\nFound concentrator with ipv6: %s\n", concentrator_ip);
            break;
        } else {
            ztimer_periodic_wakeup(ZTIMER_MSEC, &last_wakeup, 5000);
        }
    }
    return 0;
}