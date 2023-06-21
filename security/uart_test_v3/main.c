#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "periph/uart.h"

#define UART_DEV          UART_DEV(0)
#define UART_BAUDRATE     115200
#define UART_BUFSIZE      128U

typedef struct {
    uint8_t device_id;
    uint8_t dtls_psk_aes_128_key[16];
} provisioning_data_t;

provisioning_data_t provision;

static void rx_cb(void *arg, uint8_t data)
{
    static uint8_t pos = 0;
    uint8_t *buf = arg;

    buf[pos++] = data;

    if (data == '\n') {
        buf[pos] = '\0';  // Null-terminate the string

        // Parse the device id and AES key
        char *token = strtok((char*)buf, ",");
        provision.device_id = atoi(token);
        token = strtok(NULL, ",");
        for(int i=0; i<16; i++) {
            sscanf(&token[i*2], "%02hhx", &provision.dtls_psk_aes_128_key[i]);
        }
        printf("Received Device ID: %d, AES key: ", provision.device_id);
        for (int i = 0; i < 16; i++) {
            printf("%02x", provision.dtls_psk_aes_128_key[i]);
        }
        printf("\n");

        pos = 0;
        printf("ACK\n");  // Acknowledge the successful provisioning
    }
}

int main(void)
{
    uint8_t rx_mem[UART_BUFSIZE];
    
    if (uart_init(UART_DEV, UART_BAUDRATE, rx_cb, rx_mem) < 0) {
        printf("Cannot initialize UART\n");
        return 1;
    }
    return 0;
}
