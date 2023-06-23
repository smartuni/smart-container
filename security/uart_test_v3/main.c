#include "periph/uart.h"
#define UART_DEV0      UART_DEV(0)
#define UART_BAUD_RATE 115200

void uart_rx_cb(void *ctx, uint8_t data) {
    (void)ctx;

    if (data == 'A') {
        printf("Received 'A' successfully\n");
    } else {
        printf("Received unexpected data: '%c'\n", data);
    }
}

int main(void) {
    if(uart_init(UART_DEV0, UART_BAUD_RATE, uart_rx_cb, NULL) < 0) {
        printf("Cannot initialize UART\n");
        return 1;
    }

    printf("Waiting for data...\n");
    return 0;
}
