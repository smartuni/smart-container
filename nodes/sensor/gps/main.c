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
#include "ringbuffer.h"
#include "msg.h"
#include "thread_config.h"
#include "board.h"
#include "xtimer.h"
#include "gps.h"

mutex_t mutex; 

// UART
#define UART_BUFSIZE        (128U)
#define STDIO_UART_DEV      (UART_UNDEF)

typedef struct {
    char rx_mem[UART_BUFSIZE];
    ringbuffer_t rx_buf;
} uart_ctx_t;
static uart_ctx_t ctx[UART_NUMOF];

// UART device ID of GPS module
#define GPS_UART_DEV 0

// Printer
#define PRINTER_PRIO        (THREAD_PRIORITY_MAIN - 1)
static kernel_pid_t printer_pid;
static char printer_stack[THREAD_STACKSIZE_MAIN];

/**
 * Callback for receiving data from UART
*/
static void rx_cb(void *arg, uint8_t data) {
    uart_t dev = (uart_t)(uintptr_t)arg;

    ringbuffer_add_one(&ctx[dev].rx_buf, data);

    if (data == '\n') {
        msg_t msg;
        msg.content.value = (uint32_t)dev;
        msg_send(&msg, printer_pid);
    }
}

/**
 * Thread function for printing out received characters to the shell.
 * When a whole sentence is received, it tries to parse it as a result from the GPS module.
*/
static void *printer(void *arg) {
    (void)arg;
    msg_t msg;
    msg_t msg_queue[8];
    msg_init_queue(msg_queue, 8);

    while (1) {
        msg_receive(&msg);
        uart_t dev = (uart_t)msg.content.value;
        char c;
        char *result = NULL;
        size_t result_len = 0;
        size_t i = 0;

        //printf("Success: UART_DEV(%i) RX: [", dev);
        do {
            mutex_lock(&mutex);
            c = (int)ringbuffer_get_one(&(ctx[dev].rx_buf));
            result_len++; // increase length of the string
            char* temp = realloc(result, (result_len+1) * sizeof(char));
            if(temp == NULL) {
                printf("Memory allocation failed.\n");
                free(result);
                exit(EXIT_FAILURE);
            }
            result = temp;
            result[i++] = c;

            if (c == '\n') {
                //puts("]\\n");
            }
            else if (c >= ' ' && c <= '~') {
                //printf("%c", c);
            }
            else {
                //printf("0x%02x", (unsigned char)c);
            }
            mutex_unlock(&mutex);
        } while (c != '\n');
        //printf("\nReceived ==> %s\n", result);
        if(parse_gps_string(result) == EXIT_FAILURE) {
            printf("Error parsing GPS string: %s\n", result);
        }
    }

    /* this should never be reached */
    return NULL;
}

/**
 * Initializes the GPS module
*/
static int init_gps_module(void) {
    int res;

    uint32_t baud = 9600;

    /* initialize UART */
    res = uart_init(UART_DEV(GPS_UART_DEV), baud, rx_cb, (void *)GPS_UART_DEV);
    if (res == UART_NOBAUD) {
        printf("Error: Given baudrate (%u) not possible\n", (unsigned int)baud);
        return 1;
    }
    else if (res != UART_OK) {
        puts("Error: Unable to initialize UART device");
        return 1;
    }
    printf("Success: Initialized UART_DEV(%i) at %"PRIu32" baud\n", GPS_UART_DEV, baud);

    /* also test if poweron() and poweroff() work (or at least don't break
     * anything) */
    //sleep_test(dev, UART_DEV(dev));

    return 0;
}

/**
 * Sends a command to the GPS module
*/
/* static int cmd_send(int argc, char **argv) {
    (void) argc;
    (void) argv;
    uint8_t endline = (uint8_t)'\n';

    if (argc < 2) {
        printf("usage: %s <data (string)>\n", argv[0]);
        return 1;
    }

    printf("UART_DEV(%i) TX: %s\n", GPS_UART_DEV, argv[1]);
    uart_write(UART_DEV(GPS_UART_DEV), (uint8_t *)argv[1], strlen(argv[1]));
    uart_write(UART_DEV(GPS_UART_DEV), &endline, 1);
    return 0;
} */

int main(int argc, char **argv) {
    (void) argc;
    (void) argv;
    xtimer_msleep(3000);

    puts("===================================");
    puts("SMARTCONTAINER GPS SENSOR");
    puts("===================================");

   /* // JUST FOR TESTING:
    printf("$GPGGA: %d\n", parse_gps_string("$GPGGA,064951.000,2307.1256,N,12016.4438,E,1,8,0.95,39.9,M,17.8,M,,*65"));
    printf("$GPGSA: %d\n", parse_gps_string("$GPGSA,A,3,29,21,26,15,18,09,06,10,,,,,2.32,0.95,2.11*00"));
    printf("$GPGSV: %d\n", parse_gps_string("$GPGSV,3,1,09,29,36,029,42,21,46,314,43,26,44,020,43,15,21,321,39*7D"));
    printf("$GPRMC: %d\n", parse_gps_string("$GPRMC,064951.000,A,2307.1256,N,12016.4438,E,0.03,165.48,260406,3.05,W,A*2C"));
    printf("$GPVTG: %d\n", parse_gps_string("$GPVTG,165.48,T,,M,0.03,N,0.06,K,A*37"));
   */

    /* initialize ringbuffers */
    for (unsigned i = 0; i < UART_NUMOF; i++) {
        ringbuffer_init(&(ctx[i].rx_buf), ctx[i].rx_mem, UART_BUFSIZE);
    }

    init_gps_module();

    /* start the printer thread */
    printer_pid = thread_create(printer_stack, sizeof(printer_stack), PRINTER_PRIO, 0, printer, NULL, "printer");

    return 0;
}