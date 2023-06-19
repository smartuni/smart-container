/*
 * Copyright (C) 2022 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include <stdio.h>
#include "periph/gpio.h"
#include "board.h"
#include "ztimer.h"
#include "coap.h"

gpio_t waterleak = GPIO_PIN(1, 8);    // Feather Pin D5

void waterleak_callback (void *arg){
    (void) arg; /* the argument is not used*/
    send_to_concentrator("Water detected.");
}


int main(void)
{
    coap_path = "/waterleak";
    discover_concentrator();
    gpio_init_int(waterleak, GPIO_IN, GPIO_FALLING, waterleak_callback, NULL);
    puts("GPIOs example.");

    return 0;
}
