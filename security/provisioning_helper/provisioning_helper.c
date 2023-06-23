#include "string.h"
#include "provisioning_helper.h"

#define PROVISIONING_HELPER_BUF_SIZE 512
#define PROVISIONING_ENABLE_DEV 1

mtd_flashpage_t _mtd_dev = MTD_FLASHPAGE_INIT_VAL(1);
mtd_dev_t *mtd_dev = &_mtd_dev.base;

int provisioning_helper_init(void)
{    
    if(mtd_init(mtd_dev))
    {
        LOG_ERROR("Failed to initialize MTD dev.\n");
        return -1;
    }
    
    #if(PROVISIONING_ENABLE_DEV==1)
    LOG_WARNING("DEV_PROVISIONING enabled for development environment!\n");
    LOG_WARNING("Erasing provisioning page (%d).\n", PROVISIONING_FLASH_PAGE_NUMBER);
    mtd_erase(mtd_dev, PROVISIONING_FLASH_PAGE_BASE_ADDR, mtd_dev->pages_per_sector * mtd_dev->page_size);

    // Creating page buffer with random data
    char buf[128];
    random_init(0);
    random_bytes((uint8_t *)buf, sizeof(buf));

    int ret2 = mtd_write(mtd_dev, buf, PROVISIONING_FLASH_PAGE_BASE_ADDR, sizeof(buf));
    if(ret2)
    {
        LOG_ERROR("Failed to write test data to MTD.\n");
    }
    else
    {
        LOG_INFO("Initialized MTD test data with:\n");
        od_hex_dump(buf, sizeof(buf), OD_WIDTH_DEFAULT);
    }

    LOG_DEBUG("Flash page dump:\n");
    od_hex_dump((void *)PROVISIONING_FLASH_PAGE_BASE_ADDR, FLASHPAGE_SIZE, OD_WIDTH_DEFAULT);
    #endif

    LOG_INFO("Successfully initialized Provisioning helper.\n");
    return 0;
}

// #ifdef PROVISIONING_CONFIG_CONCENTRATOR /* Start Concentrator-specific provisioning */

int provisioning_helper_get_sec_save_aes_key(uint8_t *sec_save_aes_key)
{
    LOG_INFO("Inside provisioning_helper_get_sec_save_aes_key.\n");
    // getchar();

    uint8_t page_buf[PROVISIONING_HELPER_BUF_SIZE];
    int ret = mtd_read(mtd_dev, page_buf, PROVISIONING_FLASH_PAGE_BASE_ADDR, PROVISIONING_HELPER_BUF_SIZE);

    if(ret !=0)
    {
        LOG_ERROR("Provisioning helper failed - couldn't read flash memory to access PROVISIONING_FLASH_ADDRESS_SEC_SAVE_AES_KEY.\n");
        LOG_ERROR("Returned: %d\n", ret);
        return -1;
    }

    memcpy(sec_save_aes_key, page_buf + PROVISIONING_FLASH_ADDRESS_SEC_SAVE_AES_KEY, AES_KEY_SIZE);
    LOG_INFO("Provisioned PSK Key is: %x%x %x%x %x%x %x%x %x%x %x%x %x%x %x%x\n", sec_save_aes_key[0], sec_save_aes_key[1], sec_save_aes_key[2], sec_save_aes_key[3], 
        sec_save_aes_key[4], sec_save_aes_key[5], sec_save_aes_key[6], sec_save_aes_key[7],
        sec_save_aes_key[8], sec_save_aes_key[9], sec_save_aes_key[10], sec_save_aes_key[11],
        sec_save_aes_key[12], sec_save_aes_key[13], sec_save_aes_key[14], sec_save_aes_key[15]);
    od_hex_dump(sec_save_aes_key, AES_KEY_SIZE, 0);
    return 0;
}

// #endif /* End Concentrator-specific provisioning */