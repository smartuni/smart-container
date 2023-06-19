#include <stdio.h>

#include "board.h"
// #include "saul_reg.h"
#include "ztimer.h"
#include "coap.h"

int main(void) {
    coap_path = "/waterleak";

    printf("Hello World.\n");

    // saul_reg_t *adc = saul_reg_find_type(SAUL_SENSE_ANALOG);
    // if(!adc) {
    //     printf("No adc present");
    // } else {
    //     printf("Found adc: %s\n", adc->name);
    // }

    ztimer_now_t last_wakeup = ztimer_now(ZTIMER_MSEC);
    discover_concentrator();

    while(1) {
        send_to_concentrator("Test Message.");

        ztimer_periodic_wakeup(ZTIMER_MSEC, &last_wakeup, 10000);
    }

    return 0;

}