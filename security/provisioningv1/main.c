#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "periph/uart.h"
#include "periph/pm.h" 
#include "net/gnrc.h"
#include "net/gnrc/netif.h"
#include "mtd.h"

#define FLASH_KEY_PAGE 240
#define UART_DEV0 UART_DEV(0)
#define UART_BUFSIZE  (128U)
#define MTD_NUM_OF_PAGES 1
#define UART_PID 1 // Added PID
#define FLASHPAGE_SIZE 4096 
#define MAX_RETRIES 3

typedef struct {
    uint8_t device_id; // 8-bit device id [0, n]
    uint8_t ieee802154_key[16]; 
    uint8_t ipv6_addr_concentrator[16]; 
    uint8_t dtls_psk_aes_128_key[16];
    uint8_t lorawan_dev_eui[16];//Concentrator
    uint8_t lorawan_app_eui[16];//Concentrator
    uint8_t lorawan_app_key[32];//Concentrator
    uint8_t sec_save_aes_key[16]; //128-bit AES key for sec_save
} provisioning_data_t;

provisioning_data_t provision;
mtd_dev_t *mtd_dev = NULL;


void check_provisioning() {
    // calculate the start address of the page
    uint32_t addr = FLASH_KEY_PAGE * FLASHPAGE_SIZE;
    
    uint8_t buffer[sizeof(provisioning_data_t)];
    mtd_read(mtd_dev, buffer, addr, sizeof(provisioning_data_t));

    int retries = 0;

    while (memcmp(buffer, &provision, sizeof(provisioning_data_t)) != 0 && retries < MAX_RETRIES) {
        printf("Device not provisioned. Retrying provisioning...\n");
        provision_device();
        mtd_read(mtd_dev, buffer, addr, sizeof(provisioning_data_t));
        retries++;
    }

    if (retries >= MAX_RETRIES) {
        printf("Failed to provision device after %d attempts. Rebooting...\n", MAX_RETRIES);
        pm_reboot();
    }
}

void provision_device() {
    // calculate the start address of the page
    uint32_t addr = FLASH_KEY_PAGE * FLASHPAGE_SIZE;

    // erase the whole page
    mtd_erase(mtd_dev, addr, FLASHPAGE_SIZE);
    // write the provision data to the start of the page
    mtd_write(mtd_dev, (uint8_t*)&provision, addr, sizeof(provisioning_data_t));

    printf("Provisioning done successfully!\n");
    printf("ACK\n"); 
}

void store_ipv6_address() {
    gnrc_netif_t* netif = gnrc_netif_iter(NULL);  // get the first network interface
    if (netif == NULL) {
        puts("Error: No network interface found.");
        return;
    }

    ipv6_addr_t ipv6_addr;
    if (gnrc_netif_ipv6_addrs_get(netif, &ipv6_addr, sizeof(ipv6_addr)) < 0) {
        puts("Error: Failed to get IPv6 address.");
        return;
    }

    // Copy the generated IPv6 address to the provisioning data
   memcpy(provision.ipv6_addr_concentrator, &ipv6_addr, sizeof(ipv6_addr));
}

static void rx_cb(void *arg, uint8_t data)
{
    static uint8_t pos = 0;
    uint8_t *buf = arg;

    if (pos >= UART_BUFSIZE) {
        puts("Received data is too large. Ignoring...\n");
        pos = 0;
        return;
    }

    buf[pos++] = data;

    if (data == '\n') {
        buf[pos] = '\0';  // Null-terminate the string
        if (strcmp((char*)buf, "S\n") == 0) {
            store_ipv6_address();
            provision_device();
            check_provisioning();
        }
        else {
            check_provisioning();
        }
        pos = 0;
    }
}

int main(void)
{
    check_provisioning();

    uint8_t rx_mem[sizeof(provisioning_data_t)];
    
    if (uart_init(UART_DEV0, 115200, rx_cb, rx_mem) < 0) {
        printf("Cannot initialize UART\n");
        return 1;
    }
    return 0;
}
