#include "periph/uart.h"
#include "xtimer.h"
#include <string.h>

#define UART_DEV0      UART_DEV(0)
#define BUF_SIZE      1024

static char buf[BUF_SIZE];
static size_t buf_idx = 0;

static void rx_cb(void *arg, uint8_t data) {
    (void)arg;

    // add received data to buffer
    if (buf_idx < BUF_SIZE - 1) {
        buf[buf_idx++] = (char)data;

        if (data == '\n') {
            // if newline character received, terminate string and print it
            buf[buf_idx - 1] = '\0';  // replace '\n' with string termination character '\0'
            printf("Received: %s\n", buf);

            // send back an ACK
            uart_write(UART_DEV, (uint8_t*)"ACK\n", 4);

            // clear buffer
            memset(buf, 0, sizeof(buf));
            buf_idx = 0;
        }
    }
    else {
        // buffer overflow, clear buffer
        memset(buf, 0, sizeof(buf));
        buf_idx = 0;
    }
}

int main(void) {
    uart_init(UART_DEV0, 115200, rx_cb, NULL);

    // main loop
    while (1) {
        // do something
        xtimer_sleep(1);
    }
    return 0;
}
