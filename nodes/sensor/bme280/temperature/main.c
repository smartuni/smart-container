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

#define STRINGLENGTH 10
#define SEND_FREQUENCY_S 10

int main(void)
{
    puts("BME280 example.");

    saul_reg_t *temp_sensor = saul_reg_find_type_and_name(SAUL_SENSE_TEMP, "bme280");
    phydat_t temperature;
    ztimer_now_t last_wakeup = ztimer_now(ZTIMER_SEC);
    size_t convertLength = 0;
    char valueString[STRINGLENGTH];

    if(!temp_sensor){
        puts("No bme280 present");
    }
    else{
        printf("Found temperature device: %s\n", temp_sensor->name);
    }

    coap_path = "/temperature";
    discover_concentrator();

    while(1)
    {
        last_wakeup = ztimer_now(ZTIMER_SEC);
        int dimensions = saul_reg_read(temp_sensor, &temperature);
        if (dimensions < 1)
        {
            puts("Error reading temp value from device");
        }
        else{
            convertLength = fmt_s16_dfp(valueString, temperature.val[0], temperature.scale);
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
