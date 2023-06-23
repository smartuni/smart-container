#include <string.h>
#include <stdint.h>

#include "log.h"
#include "fmt.h"
#include "od.h"
#include "random.h"
#include "mtd.h"
#include "mtd_flashpage.h"

#include "credman_helper.h"

#define DEV_PROVISIONING 1

int init_provisioning(mtd_dev_t *mtd_dev)
{
    if(mtd_init(mtd_dev))
    {
        LOG_ERROR("Failed to initialize MTD dev.\n");
        return -1;
    }

    int ret = mtd_erase(mtd_dev, CREDMAN_FLASH_PAGE_START_ADDR, mtd_dev->pages_per_sector * mtd_dev->page_size);

    #if(DEV_PROVISIONING==1)
    LOG_WARNING("DEV_PROVISIONING enabled for development environment!\n");
    
    // Creating page buffer with random data
    char buf[CREDMAN_FLASH_ADDRESS_DTLS_PSK_AES_KEY + CREDMAN_FLASH_LEN_DTLS_PSK_AES_KEY];
    random_bytes((uint8_t *)buf, sizeof(buf));

    int ret2 = mtd_write(mtd_dev, buf, CREDMAN_ADDRESS(0), sizeof(buf));
    if(ret2)
    {
        LOG_ERROR("Failed to write test data to MTD.\n");
    }
    else
    {
        LOG_INFO("Initialized MTD test data with:\n");
        // od_hex_dump(buf, sizeof(buf), OD_WIDTH_DEFAULT);
    }

    LOG_DEBUG("Flash page dump:\n");
    // od_hex_dump((void *)CREDMAN_FLASH_PAGE_START_ADDR, FLASHPAGE_SIZE, OD_WIDTH_DEFAULT);
    #endif

    return ret;
}

int flash_read(uint8_t addr, uint8_t *dest, size_t size) 
{
    uint8_t* page_ptr = (uint8_t*)flashpage_addr(CREDMAN_FLASH_PAGE_NUMBER);

    memcpy(dest, page_ptr + addr, size);

    return size; 
}

int read_psk(mtd_dev_t *mtd_dev, uint8_t *psk_id, uint8_t *psk_key)
{   
    if(mtd_read(mtd_dev, psk_id, CREDMAN_ADDRESS(CREDMAN_FLASH_ADDRESS_DEVICE_ID), CREDMAN_FLASH_LEN_DEVICE_ID))
    {
        LOG_ERROR("Credman helper failed - couldn't read flash memory to access CREDMAN_FLASH_ADDRESS_DEVICE_ID.\n");
        return -1;
    }

    if(mtd_read(mtd_dev, psk_key, CREDMAN_ADDRESS(CREDMAN_FLASH_ADDRESS_DTLS_PSK_AES_KEY), CREDMAN_FLASH_LEN_DTLS_PSK_AES_KEY))
    {
        LOG_ERROR("Credman helper failed - couldn't read flash memory to access CREDMAN_FLASH_ADDRESS_DTLS_PSK_AES_KEY.\n");
        return -1;
    }

    return 1;
}