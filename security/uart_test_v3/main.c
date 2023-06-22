#include "periph/uart.h"
#include <string.h>
#define UART_DEV0      UART_DEV(0)
#define UART_BAUD_RATE 96000
#define RX_BUFFER_SIZE 256

char rx_buffer[RX_BUFFER_SIZE];
int rx_idx = 0;

void uart_rx_cb(void *ctx, uint8_t data) {
    (void)ctx;

    // Add received data to buffer
    rx_buffer[rx_idx++] = data;

    // Check for end of transmission or buffer overflow
    if (data == '\n' || rx_idx == RX_BUFFER_SIZE) {
        // Null-terminate the string
        rx_buffer[rx_idx] = '\0';

        // Reset index for next message
        rx_idx = 0;

        printf("Received key: %s\n", rx_buffer);
    }
}

int main(void) {
    memset(rx_buffer, 0, sizeof(rx_buffer));
    uart_init(UART_DEV0, UART_BAUD_RATE, uart_rx_cb, NULL);
    return 0;
}

