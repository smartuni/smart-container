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

gpio_t reedSwitch = GPIO_PIN(PORT_E, 4); 

void reedswitch_callback (void *arg)
{
    (void) arg; /* the argument is not used */
    send_to_concentrator("Door opened");
}


int main(void)
{
    coap_path = "/door";
    discover_concentrator();
    gpio_init_int(reedSwitch, GPIO_IN_PU, GPIO_RISING, reedswitch_callback, NULL);
    puts("GPIOs example.");

    return 0;
}
