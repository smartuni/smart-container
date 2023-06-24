#include <stdio.h>
#include "periph/uart.h"
#include "thread.h"
#include "xtimer.h"

#define UART_DEV0      UART_DEV(0)
#define UART_BAUD_RATE 115200

char stack[THREAD_STACKSIZE_MAIN];

void rx_cb(void *arg, uint8_t data)
{
    (void)arg;
    printf("Received: %c\n", data);
}

void *uart_reader(void *arg)
{
    (void)arg;
    printf("Thread started\n");
    
    uart_rx_cb_t uart_cb = rx_cb;
    printf("Callback function set\n");

    if (uart_init(UART_DEV0, UART_BAUD_RATE, uart_cb, NULL) != UART_OK) {
        printf("UART initialization failed\n");
        return NULL;
    }

    printf("UART initialization successful\n");
    while(1) {
        printf("Sleeping for 1 minute\n");
        xtimer_sleep(60);
        printf("Awake, ready to receive data\n");
    }

    return NULL;
}

int main(void)
{
    printf("Main function started\n");

    char* thread_name = "uart_reader";
    printf("Creating thread: %s\n", thread_name);
    if(thread_create(stack, sizeof(stack), THREAD_PRIORITY_MAIN - 1, THREAD_CREATE_STACKTEST, uart_reader, NULL, thread_name) == -EINVAL) {
        printf("Thread creation failed\n");
        return 1;
    }
    printf("Thread created successfully\n");
    
    while(1) {
        printf("Main loop, sleeping for 1 minute\n");
        xtimer_sleep(60);
        printf("Main loop, awake\n");
    }
    
    return 0;
}
