#include <stdio.h>
#include "periph/uart.h"

#include "shell.h"

#define UART_BAUDRATE 115200
#define UART_DEV0      UART_DEV(0)
// #define RX_BUFSIZE    33

// static char rx_buf[RX_BUFSIZE];
static char line_buf[60];


static int provisioning_command(int argc, char **argv)
{
    
    (void)argc;
    (void)argv;
    //printf("[XFA TEST 2 OK]\n");
    if (argc != 2) {
        printf("Missing device ID\n");
        return 1;

    }
    printf("%s\n", argv[1]);

    return 0;
}


// static void rx_cb(void *arg, uint8_t data)
// {
//     (void)arg;
//     static size_t pos = 0;
//     rx_buf[pos++] = data;

//     if (pos >= sizeof(rx_buf)) {
//         pos = 0;
//     }

//     if (data == '\n') {
//         printf("Received key: ");
//         for (size_t i = 0; i < pos; i++) {
//             printf("%c", rx_buf[i]);
//         }
//         printf("\n");
//         pos = 0;
//     }
// }

SHELL_COMMAND(provisioning, "provision  keys", provisioning_command);


int main(void)
{
//     (void) getchar();
//    int res = uart_init(UART_DEV0, UART_BAUDRATE, rx_cb, NULL);
// if (res < 0) {
//     printf("UART initialization failed!\n");
//     return res;
// }
    shell_run(NULL, line_buf, sizeof(line_buf));
return 0;

}
