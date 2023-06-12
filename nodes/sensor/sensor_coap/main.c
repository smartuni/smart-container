
/*
Sensor node code which reads a sensor periodacly or event based and sends the data to the concentrator node via coap
*/


//include 
#include "coap.h"
#include "temperature.h"

// declare functions
static size_t discover_concentrator(void);

//declare variables
#define SLEEP_TIME 10000
#define WAIT_TIME 5000
#define VALUE_LENGTH 10
char sensor_value[VALUE_LENGTH];

// start main function
int main(void)
{   
    // intitialize timer
    ztimer_now_t last_wakeup = ztimer_now(ZTIMER_MSEC);

    // initialize sensor
    // init_sensor();

    // discover concentrator node via coap multicast
    discover_concentrator();    

    // periodically read and send sensor data
    while(1) {
        puts("Get sensor value");

        if (!read_sensor(sensor_value, VALUE_LENGTH)) {
            puts("Send data to concentrator");
            send_req(concentrator_ip, "5683", coap_path, sensor_value, COAP_POST, _std_resp_handler);
            
            puts("Going to sleep\n");
            ztimer_periodic_wakeup(ZTIMER_MSEC, &last_wakeup, SLEEP_TIME);
            puts("Woke up");
        }                   
    }
    
    return 0;
}