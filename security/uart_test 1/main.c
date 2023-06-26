#include <stdio.h>
#include "periph/uart.h"

#define UART_BAUDRATE 115200
#define UART_DEV0      UART_DEV(0)
#define RX_BUFSIZE    33

static char rx_buf[RX_BUFSIZE];

static void rx_cb(void *arg, uint8_t data)
{
    (void)arg;
    static size_t pos = 0;
    rx_buf[pos++] = data;

    if (pos >= sizeof(rx_buf)) {
        pos = 0;
    }

    if (data == '\n') {
        printf("Received key: ");
        for (size_t i = 0; i < pos; i++) {
            printf("%c", rx_buf[i]);
        }
        printf("\n");
        pos = 0;
    }
}

int main(void)
{
    (void) getchar();
   int res = uart_init(UART_DEV0, UART_BAUDRATE, rx_cb, NULL);
if (res < 0) {
    printf("UART initialization failed!\n");
    return res;
}
return 0;

}
