#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "net/gnrc.h"
#include "net/gnrc/netif.h"
#include "mtd.h"
#include "shell.h"
#include "provisioning_helper.h"
#define FLASH_KEY_PAGE 240

#define MTD_NUM_OF_PAGES 1
#define FLASHPAGE_SIZE 4096 
#define MAX_RETRIES 3
#define PROVISIONING_HELPER_BUF_SIZE 256

typedef struct {
    uint8_t device_id;
    uint8_t ieee802154_key[16]; 
    uint8_t ipv6_addr_concentrator[16]; 
    uint8_t dtls_psk_aes_128_key[16];
   //uint8_t lorawan_dev_eui[16];//Concentrator
   //uint8_t lorawan_app_eui[16];//Concentrator
   //uint8_t lorawan_app_key[32];//Concentrator
    //uint8_t sec_save_aes_key[16]; //128-bit AES key for sec_save
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

 static int provisioning_command(int argc, char **argv) { 
    
    //LOG_WARNING("DEV_PROVISIONING enabled for development environment!\n");
    //LOG_WARNING("Erasing provisioning page (%d).\n", PROVISIONING_FLASH_PAGE_NUMBER);
    mtd_erase(mtd_dev, PROVISIONING_FLASH_PAGE_BASE_ADDR, mtd_dev->pages_per_sector * mtd_dev->page_size);

    // Creating page buffer with random data
    LOG_INFO("Filling MTD with test values:\n");
    
    int ret2 = 0;

    (void)argc;
    (void)argv;

    if (argc != 4) {
        printf("Error: Invalid number of arguments. Expected 4 keys, got %d\n", argc - 1);
        return 1;
    }

    provision.device_id = atoi(argv[1]);
    printf("%s\n", argv[1]);
    /* Provisioning - Device ID */
    ret2 += mtd_write(mtd_dev, argv[1], 
        PROVISIONING_ADD_TO_BASE_ADDRESS(PROVISIONING_FLASH_ADDRESS_DEVICE_ID), 
        PROVISIONING_FLASH_LEN_DEVICE_ID);

     /* Provisioning - IEEE 802.15.4 Key */
    ret2 += mtd_write(mtd_dev, argv[2], 
        PROVISIONING_ADD_TO_BASE_ADDRESS(PROVISIONING_FLASH_ADDRESS_IEEE802154_KEY), 
        PROVISIONING_FLASH_LEN_IEEE802154_KEY);


     /* Provisioning - Concentrator node IPv6 addresss */
   // ret2 += mtd_write(mtd_dev, argv[3], 
      //  PROVISIONING_ADD_TO_BASE_ADDRESS(PROVISIONING_FLASH_ADDRESS_CONCENTRATOR_IPV6_ADDR), 
       // PROVISIONING_FLASH_LEN_CONCENTRATOR_IPV6_ADDR);

    /* Provisioning - DTLS PSK AES128 Key*/
    ret2 += mtd_write(mtd_dev, argv[3], 
        PROVISIONING_ADD_TO_BASE_ADDRESS(PROVISIONING_FLASH_ADDRESS_DTLS_PSK_AES_KEY), 
        PROVISIONING_FLASH_LEN_DTLS_PSK_AES_KEY);

    //check_provisioning();
    return 0;
}

SHELL_COMMAND(provisioning, "device_id ieee802154_key dtls_psk_aes_128_key", provisioning_command);


int main(void)
{
    //check_provisioning();

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(NULL, line_buf, sizeof(line_buf));

     LOG_INFO("Initialized MTD test data with:\n");
        char buf[PROVISIONING_HELPER_BUF_SIZE];
        mtd_read(mtd_dev, buf, PROVISIONING_FLASH_PAGE_BASE_ADDR, PROVISIONING_HELPER_BUF_SIZE);
    return 0;
}