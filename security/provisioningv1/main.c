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
// #define FLASHPAGE_SIZE 4096 
#define MAX_RETRIES 3
#define PROVISIONING_HELPER_BUF_SIZE 256

mtd_dev_t *mtd_dev = NULL;


static int check_cmd(int argc, char **argv) { 
    
    //LOG_WARNING("DEV_PROVISIONING enabled for development environment!\n");
    //LOG_WARNING("Erasing provisioning page (%d).\n", PROVISIONING_FLASH_PAGE_NUMBER);
    (void)argc;
    (void)argv;

    // uint8_t buf[512];
    // mtd_read(mtd_dev, buf, PROVISIONING_FLASH_PAGE_BASE_ADDR, sizeof(buf));
    // od_hex_dump(buf, sizeof(buf), OD_WIDTH_DEFAULT);


    uint8_t buf[16];
    provisioning_helper_get_sec_save_aes_key(buf);
    od_hex_dump(buf, sizeof(buf), OD_WIDTH_DEFAULT);

    // Creating page buffer with random data
   // LOG_INFO("Filling MTD with test values:\n");

    //check_provisioning();
    return 0;
}

 static int provisioning_command(int argc, char **argv) { 
    
    //LOG_WARNING("DEV_PROVISIONING enabled for development environment!\n");
    //LOG_WARNING("Erasing provisioning page (%d).\n", PROVISIONING_FLASH_PAGE_NUMBER);
    mtd_erase(mtd_dev, PROVISIONING_FLASH_PAGE_BASE_ADDR, mtd_dev->pages_per_sector * mtd_dev->page_size);

    // Creating page buffer with random data
   // LOG_INFO("Filling MTD with test values:\n");
    
    int ret2 = 0;

    (void)argc;
    (void)argv;

    if (argc != 6) {
        printf("Error: Invalid number of arguments. Expected 5 keys, got %d\n", argc - 1);
        return 1;
    }

    /* Provisioning - Device ID */
    ret2 += mtd_write(mtd_dev, argv[1], 
        PROVISIONING_ADD_TO_BASE_ADDRESS(PROVISIONING_FLASH_ADDRESS_DEVICE_ID), 
        PROVISIONING_FLASH_LEN_DEVICE_ID);

     /* Provisioning - IEEE 802.15.4 Key */
    ret2 += mtd_write(mtd_dev, argv[2], 
        PROVISIONING_ADD_TO_BASE_ADDRESS(PROVISIONING_FLASH_ADDRESS_IEEE802154_KEY), 
        PROVISIONING_FLASH_LEN_IEEE802154_KEY);

     /* Provisioning - Concentrator node IPv6 addresss */
    ret2 += mtd_write(mtd_dev, argv[3], 
        PROVISIONING_ADD_TO_BASE_ADDRESS(PROVISIONING_FLASH_ADDRESS_CONCENTRATOR_IPV6_ADDR), 
        PROVISIONING_FLASH_LEN_CONCENTRATOR_IPV6_ADDR);    

        /* Provisioning - DTLS PSK AES128 Key*/
    ret2 += mtd_write(mtd_dev, argv[4], 
        PROVISIONING_ADD_TO_BASE_ADDRESS(PROVISIONING_FLASH_ADDRESS_DTLS_PSK_AES_KEY), 
        PROVISIONING_FLASH_LEN_DTLS_PSK_AES_KEY);

    /* Provisioning - Secure Save AES-128 Key */
   ret2 += mtd_write(mtd_dev, argv[5], 
       PROVISIONING_ADD_TO_BASE_ADDRESS(PROVISIONING_FLASH_ADDRESS_SEC_SAVE_AES_KEY), 
       PROVISIONING_FLASH_LEN_SEC_SAVE_AES_KEY);


    uint8_t buf[16];
    provisioning_helper_get_sec_save_aes_key(buf);
    od_hex_dump(buf, sizeof(buf), OD_WIDTH_DEFAULT);

    //check_provisioning();
    return 0;
}

SHELL_COMMAND(provisioning, "device_id ieee802154_key concentrator_ipv6 dtls_psk_aes_128_key sec_save_aes_key", provisioning_command);
SHELL_COMMAND(check, "check", check_cmd);


int main(void)
{
    //check_provisioning();

    char line_buf[256];
    shell_run(NULL, line_buf, sizeof(line_buf));

    //  LOG_INFO("Initialized MTD test data with:\n");
    //     char buf[PROVISIONING_HELPER_BUF_SIZE];
    //     mtd_read(mtd_dev, buf, PROVISIONING_FLASH_PAGE_BASE_ADDR, PROVISIONING_HELPER_BUF_SIZE);
    return 0;
}