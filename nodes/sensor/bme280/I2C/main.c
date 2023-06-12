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

int main(void)
{
    puts("BME280 example.");

    saul_reg_t *temp_sensor = saul_reg_find_type_and_name(SAUL_SENSE_TEMP, "bme280");
    saul_reg_t *humid_sensor = saul_reg_find_type(SAUL_SENSE_HUM);
    saul_reg_t *pressure_sensor = saul_reg_find_type(SAUL_SENSE_PRESS);

    if(!temp_sensor){
        puts("No temperature sensor present");
    }
    else{
        printf("Found temperature device: %s\n", temp_sensor->name);
    }

    if(!humid_sensor){
        puts("No humidity sensor present");
    }
    else{
        printf("Found humidity device: %s\n", temp_sensor->name);
    }

    if(!pressure_sensor){
        puts("No pressure sensor present");
    }
    else{
        printf("Found pressure device: %s\n", temp_sensor->name);
    }

    ztimer_now_t last_wakeup = ztimer_now(ZTIMER_MSEC);

    while(1)
    {
        phydat_t temperature;
        phydat_t humidity;
        phydat_t pressure;
        int dimensions = saul_reg_read(temp_sensor, &temperature);
        if (dimensions < 1)
        {
            puts("Error reading temp value from device");
        }
        phydat_dump(&temperature, dimensions);
        dimensions = saul_reg_read(humid_sensor, &humidity);
        if (dimensions < 1)
        {
            puts("Error reading humidity value from device");
        }
        dimensions = saul_reg_read(pressure_sensor, &pressure);
        phydat_dump(&humidity, dimensions);
        if (dimensions < 1)
        {
            puts("Error reading pressure value from device");
        }
        phydat_dump(&pressure, dimensions);

        ztimer_periodic_wakeup(ZTIMER_MSEC, &last_wakeup, 1000);
    }
}
