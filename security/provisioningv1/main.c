#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "net/loramac.h"
#include "semtech_loramac.h"
#include "net/ieee802154/submac.h"
#include "periph/uart.h"
#include "periph/flashpage.h"
#include "log.h"
#include "periph/pm.h" 
#include "net/gnrc.h"
#include "net/gnrc/netif.h"

#define FLASH_KEY_PAGE 240
#define UART_DEV0 UART_DEV(0)
#define UART_BUFSIZE  (128U)

typedef struct {
    uint8_t device_id; // 8-bit device id [0, n]
    uint8_t ieee802154_key[16]; 
    uint8_t ipv6_addr_concentrator[16]; 
    uint8_t dtls_psk_aes_128_key[16];
    uint8_t lorawan_dev_eui[16];
    uint8_t lorawan_app_eui[16];
    uint8_t lorawan_app_key[32];
    uint8_t sec_save_aes_key[16]; //128-bit AES key for sec_save
    uint8_t prev_dtls_psk_aes_128_keys[9*16]; // keys from previous 9 devices
    uint8_t prev_sec_save_aes_keys[9*16];     // keys from previous 9 devices
} provisioning_data_t;

provisioning_data_t provision;

void panic() {
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

void provision_device() {
    flashpage_erase(FLASH_KEY_PAGE);
    
    if(flashpage_write_raw(FLASH_KEY_PAGE, &provision, sizeof(provision)) < 0){
        LOG_ERROR("Failed to write to flash page!\n");
        pm_reboot();  
    }

    provisioning_data_t verify_provision;
    memcpy(&verify_provision, (uint8_t*)flashpage_addr(FLASH_KEY_PAGE), sizeof(provision));
    if (memcmp(&verify_provision, &provision, sizeof(provision)) != 0) {
        LOG_ERROR("Provisioning failed!\n");
        pm_reboot();  
    }

    LOG_INFO("Provisioning done successfully!\n");
    printf("ACK\n"); 
}

void store_ipv6_address(kernel_pid_t pid) {
    gnrc_netif_t* netif = gnrc_netif_get_by_pid(pid);
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
    store_ipv6_address(/* PID */);
    check_provisioning();

    uint8_t rx_mem[sizeof(provisioning_data_t)];
    
    if (uart_init(UART_DEV0, 115200, rx_cb, rx_mem) < 0) {
        LOG_ERROR("Cannot initialize UART\n");
        return 1;
    }
    return 0;
}
