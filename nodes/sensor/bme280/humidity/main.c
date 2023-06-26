/*
 * Copyright (C) 2022 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */
#include <stdio.h>

// Not needed when using saul
//#include "board.h"
//#include "bmx280.h"
#include "saul_reg.h"
#include "ztimer.h"
#include "phydat.h"
#include "coap.h"
#include "fmt.h"

/* ------------------------------------------------ */
/*          Start security initialization           */
/* ------------------------------------------------ */
#include "provisioning_helper.h"
//#include "sec_link_layer.h"
//static ieee802154_sec_context_t link_layer_sec_ctx;
/* ------------------------------------------------ */
/*           End security initialization            */
/* ------------------------------------------------ */

#define STRINGLENGTH 10
#define SEND_FREQUENCY_S 10

int main(void)
{
    /* ------------------------------------------------ */
    /*          Start security initialization           */
    /* ------------------------------------------------ */
    provisioning_helper_init();
    //sec_link_layer_init(&link_layer_sec_ctx);
    /* ------------------------------------------------ */
    /*           End security initialization            */
    /* ------------------------------------------------ */
    puts("BME280 example.");

    saul_reg_t *humid_sensor = saul_reg_find_type(SAUL_SENSE_HUM);
    phydat_t humidity;
    ztimer_now_t last_wakeup = ztimer_now(ZTIMER_SEC);
    size_t convertLength = 0;
    char valueString[STRINGLENGTH];

    if(!humid_sensor){
        puts("No bme280 sensor present");
    }
    else{
        printf("Found sensor device: %s\n", humid_sensor->name);
    }

    coap_path = "/humidity";
    discover_concentrator();

    while(1)
    {
        last_wakeup = ztimer_now(ZTIMER_SEC);
        int dimensions = saul_reg_read(humid_sensor, &humidity);
        if (dimensions < 1)
        {
            puts("Error reading humidity value from device");
        }
        else{
            convertLength = fmt_s16_dfp(valueString, humidity.val[0], humidity.scale);
            if (convertLength < STRINGLENGTH){
                valueString[convertLength] = '\0';
                send_to_concentrator(valueString);
                //puts(valueString);
            }
            else{
                puts("Error converting read value");
            }
        }
        ztimer_periodic_wakeup(ZTIMER_SEC, &last_wakeup, SEND_FREQUENCY_S);
    }
}
