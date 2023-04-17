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

/* [TASK 2: define button and led1 here] */
gpio_t reedSwitch = GPIO_PIN(PORT_E, 4);    // -> D2 arduino pins (https://doc.riot-os.org/group__boards__pba-d-01-kw2x.html)
gpio_t led0 = GPIO_PIN(PORT_D, 6);
gpio_mode_t led0_mode = GPIO_OUT;

/* [TASK 2: write the callback function here] */

void reedswitch_callback (void *arg)
{
    (void) arg; /* the argument is not used */
    if (!gpio_read(reedSwitch)) {
        gpio_clear(led0);
    }
    else {
        gpio_set(led0);
    }
}


int main(void)
{
    gpio_init_int(reedSwitch, GPIO_IN_PU, GPIO_BOTH, reedswitch_callback, NULL);
    puts("GPIOs example.");

    /* [TASK 1: initialize and use led0 here] */

    return 0;
}
