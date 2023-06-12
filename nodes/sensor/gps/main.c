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
#include "coap.h"

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
        handle_gps_msg(result);
    }

    /* this should never be reached */
    return NULL;
}

/**
 * Initializes the GPS module
*/
static int init_gps_module(uart_t dev) {
    int res;

    uint32_t baud = 9600;

    /* initialize UART */
    res = uart_init(dev, baud, rx_cb, (void *)dev);
    if (res == UART_NOBAUD) {
        printf("Error: Given baudrate (%u) not possible\n", (unsigned int)baud);
        return 1;
    }
    else if (res != UART_OK) {
        puts("Error: Unable to initialize UART device");
        return 1;
    }
    printf("Success: Initialized UART_DEV(%i) at %"PRIu32" baud\n", dev, baud);

    /* also test if poweron() and poweroff() work (or at least don't break
     * anything) */
    //sleep_test(dev, UART_DEV(dev));

    return 0;
}

/**
 * Sends a command to the GPS module
*/
static int send_cmd(uart_t dev, const char cmd[]) {
    printf("send_cmd -> %s\r\n", cmd);
    uart_write(dev, (uint8_t*)cmd, strlen(cmd));
    const char crlf[2] = "\r\n";
    uart_write(dev, (uint8_t*)crlf, 2);

    return 0;
}

int main(int argc, char **argv) {
    (void) argc;
    (void) argv;
    xtimer_msleep(3000);

    puts("===================================");
    puts("SMART-CONTAINER GPS SENSOR");
    puts("===================================");

    /* initialize ringbuffers */
    for (unsigned i = 0; i < UART_NUMOF; i++) {
        ringbuffer_init(&(ctx[i].rx_buf), ctx[i].rx_mem, UART_BUFSIZE);
    }

    uart_t uart_gps = UART_DEV(GPS_UART_DEV);
    init_gps_module(uart_gps);

    /* start the printer thread */
    printer_pid = thread_create(printer_stack, sizeof(printer_stack), PRINTER_PRIO, 0, printer, NULL, "printer");

    while(true) {
        // While GPS data not available, check every second if valid
        printf("Waiting for valid GPS data...\n");
        while(!gpsDataValid) {
            xtimer_sleep(GPS_POLL_INTERVAL_SEC);
        }
        // Send to Sleep mode if valid
        send_cmd(uart_gps, "$PMTK161,0*28");
        printf("GPS module was sent to sleep mode\n");
        // Wait for 10 sec. and then wake up
        xtimer_sleep(GPS_SEND_INTERVAL_SEC);
        gpsDataValid = false;
        send_cmd(uart_gps, "$PMTK161,0*28");
        printf("GPS module woke up from sleep mode\n");
    }

    return 0;
}