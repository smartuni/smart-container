/*
 * Copyright (C) 2023 Maik Lorenz
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     examples
 * @{
 *
 * @file
 * @brief       GPS sensor app
 *
 * @author      Maik Lorenz <lorenz.maik@web.de>
 *
 * @}
 */

#include <stdio.h>
#include "periph/uart.h"

void rx_cb(void *arg, uint8_t data) {
    (void) arg; /* argument not used */
    printf("uart received -> %d\n", data);
}

int main(void)
{
    puts("Hello, RIOT GPS!");
    int ret = 0;
    
    uart_t uart2 = 1;
    ret = uart_init(uart2, 9600, (uart_rx_cb_t) rx_cb, NULL);
    printf("uart_init -> %d\n", ret);

    return 0;
}
