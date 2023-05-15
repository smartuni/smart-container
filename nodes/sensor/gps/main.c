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
#include <string.h>
#include <stdlib.h>
#include "fmt.h"
#include "minmea.h"
#include "periph/uart.h"
#ifdef MODULE_STDIO_UART
#include "stdio_uart.h"
#endif
#include "ringbuffer.h"
#include "msg.h"
#include "thread_config.h"
#include "board.h"

void minmea_demo(void) {
    const char *_gll = "$GNGLL,5229.0178,N,01326.7605,E,114350.000,A,A*45";
    struct minmea_sentence_gll frame;

    int res = minmea_parse_gll(&frame, _gll);
    if (!res) {
        print_str("FAILURE: error parsing GPS sentence\n");
    }
    else {
        print_str("parsed coordinates: lat=");
        print_float(minmea_tocoord(&frame.latitude), 6);
        print_str(" lon=");
        print_float(minmea_tocoord(&frame.longitude), 6);
    }
}

#define UART_BUFSIZE        (128U)
#define STDIO_UART_DEV      (UART_UNDEF)

typedef struct {
    char rx_mem[UART_BUFSIZE];
    ringbuffer_t rx_buf;
} uart_ctx_t;
static uart_ctx_t ctx[UART_NUMOF];

#define PRINTER_PRIO        (THREAD_PRIORITY_MAIN - 1)
static kernel_pid_t printer_pid;
static char printer_stack[THREAD_STACKSIZE_MAIN];

static void rx_cb(void *arg, uint8_t data) {
    uart_t dev = (uart_t)(uintptr_t)arg;

    ringbuffer_add_one(&ctx[dev].rx_buf, data);

    if (data == '\n') {
        msg_t msg;
        msg.content.value = (uint32_t)dev;
        msg_send(&msg, printer_pid);
    }
}

static void *printer(void *arg) {
    (void)arg;
    msg_t msg;
    msg_t msg_queue[8];
    msg_init_queue(msg_queue, 8);

    while (1) {
        msg_receive(&msg);
        uart_t dev = (uart_t)msg.content.value;
        char c;

        printf("Success: UART_DEV(%i) RX: [", dev);
        do {
            c = (int)ringbuffer_get_one(&(ctx[dev].rx_buf));
            if (c == '\n') {
                puts("]\\n");
            }
            else if (c >= ' ' && c <= '~') {
                printf("%c", c);
            }
            else {
                printf("0x%02x", (unsigned char)c);
            }
        } while (c != '\n');
    }

    /* this should never be reached */
    return NULL;
}

static int init_gps_module(void) {
    int res;

    int dev = 0;
    uint32_t baud = 9600;

    /* initialize UART */
    res = uart_init(UART_DEV(dev), baud, rx_cb, (void *)dev);
    if (res == UART_NOBAUD) {
        printf("Error: Given baudrate (%u) not possible\n", (unsigned int)baud);
        return 1;
    }
    else if (res != UART_OK) {
        puts("Error: Unable to initialize UART device");
        return 1;
    }
    printf("Success: Initialized UART_DEV(%i) at BAUD %"PRIu32"\n", dev, baud);

    /* also test if poweron() and poweroff() work (or at least don't break
     * anything) */
    //sleep_test(dev, UART_DEV(dev));

    return 0;
}

int main(void) {
    puts("Hello from RIOT GPS Sensor!");
    minmea_demo();
    init_gps_module();

    /* start the printer thread */
    printer_pid = thread_create(printer_stack, sizeof(printer_stack), PRINTER_PRIO, 0, printer, NULL, "printer");

    return 0;
}