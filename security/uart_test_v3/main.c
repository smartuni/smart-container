#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "periph/uart.h"
#include "periph/flashpage.h"
//#include "log.h"
#include "periph/pm.h"

#define FLASH_KEY_PAGE 240
#define UART_DEV0 UART_DEV(0)
#define UART_BUFSIZE  (128U)

typedef struct {
    uint8_t device_id; 
    uint8_t dtls_psk_aes_128_key[16];
} provisioning_data_t;

provisioning_data_t provision;

/*

panic() {
    while (1) {}
}

void check_provisioning() {
    uint8_t* key_ptr = (uint8_t*)flashpage_addr(FLASH_KEY_PAGE);
    uint8_t* end_ptr = key_ptr + sizeof(provision);
    uint8_t* provision_ptr = (uint8_t*)&provision;

    for (; key_ptr < end_ptr; key_ptr++, provision_ptr++) {
        if (*provision_ptr == 0xFF) continue;
        if (*key_ptr != *provision_ptr) {
            LOG_ERROR("Device not provisioned. Please provision the device first!\n");
            pm_reboot();  //panic()
        }
    }
}
*/

void provision_device(void) {
    flashpage_erase(FLASH_KEY_PAGE);
    
    flashpage_write_page(FLASH_KEY_PAGE, &provision);

    provisioning_data_t verify_provision;
    memcpy(&verify_provision, (uint8_t*)flashpage_addr(FLASH_KEY_PAGE), sizeof(provision));
    if (memcmp(&verify_provision, &provision, sizeof(provision)) != 0) {
        printf("Provisioning failed!\n");
        pm_reboot();  
    }

    printf("Provisioning done successfully!\n");
    printf("ACK\n"); 
}


static void rx_cb(void *arg, uint8_t data)
{
    static uint8_t pos = 0;
    uint8_t *rx_mem = arg;
    rx_mem[pos] = data;

    if (pos == sizeof(provisioning_data_t) - 1) {
        memcpy(&provision, rx_mem, sizeof(provisioning_data_t));
        provision_device();
        pos = 0;
    } else {
        pos++;
    }
}

int main(void)
{
    (void) getchar();
    //check_provisioning();

    uint8_t rx_mem[sizeof(provisioning_data_t)];
    
    if (uart_init(UART_DEV0, 115200, rx_cb, rx_mem) < 0) {
        printf("Cannot initialize UART\n");
        return 1;
    }
    return 0;
}

