#include "string.h"
#include "provisioning_helper.h"

// #define PROVISIONING_CONFIG_CONCENTRATOR 
// #define PROVISIONING_ENABLE_DEV 1

#define PROVISIONING_HELPER_BUF_SIZE 256

static mtd_flashpage_t _mtd_dev = MTD_FLASHPAGE_INIT_VAL(1);
static mtd_dev_t *mtd_dev = &_mtd_dev.base;

int provisioning_helper_init(void)
{    
    if(mtd_init(mtd_dev))
    {
        LOG_ERROR("Failed to initialize MTD dev.\n");
        return -1;
    }
    
    #if(PROVISIONING_ENABLE_DEV==1)
    provisioning_helper_init_dev();
    #endif

    LOG_INFO("Successfully initialized Provisioning helper.\n");
    return 0;
}

void provisioning_helper_init_dev(void)
{
    LOG_WARNING("DEV_PROVISIONING enabled for development environment!\n");
    LOG_WARNING("Erasing provisioning page (%d).\n", PROVISIONING_FLASH_PAGE_NUMBER);
    mtd_erase(mtd_dev, PROVISIONING_FLASH_PAGE_BASE_ADDR, mtd_dev->pages_per_sector * mtd_dev->page_size);

    // Creating page buffer with random data
    LOG_INFO("Filling MTD with test values:\n");
    
    int ret2 = 0;

    /* Provisioning - Device ID */
    ret2 += mtd_write(mtd_dev, PROVISIONING_FLASH_DEV_DEVICE_ID, 
        PROVISIONING_ADD_TO_BASE_ADDRESS(PROVISIONING_FLASH_ADDRESS_DEVICE_ID), 
        PROVISIONING_FLASH_LEN_DEVICE_ID);
    
    /* Provisioning - IEEE 802.15.4 Key */
    ret2 += mtd_write(mtd_dev, PROVISIONING_FLASH_DEV_IEEE802154_KEY, 
        PROVISIONING_ADD_TO_BASE_ADDRESS(PROVISIONING_FLASH_ADDRESS_IEEE802154_KEY), 
        PROVISIONING_FLASH_LEN_IEEE802154_KEY);

    /* Provisioning - Concentrator node IPv6 addresss */
    ret2 += mtd_write(mtd_dev, PROVISIONING_FLASH_DEV_CONCENTRATOR_IPV6_ADDR, 
        PROVISIONING_ADD_TO_BASE_ADDRESS(PROVISIONING_FLASH_ADDRESS_CONCENTRATOR_IPV6_ADDR), 
        PROVISIONING_FLASH_LEN_CONCENTRATOR_IPV6_ADDR);

    /* Provisioning - DTLS PSK AES128 Key*/
    ret2 += mtd_write(mtd_dev, PROVISIONING_FLASH_DEV_DTLS_PSK_AES_KEY, 
        PROVISIONING_ADD_TO_BASE_ADDRESS(PROVISIONING_FLASH_ADDRESS_DTLS_PSK_AES_KEY), 
        PROVISIONING_FLASH_LEN_DTLS_PSK_AES_KEY);

    /************************************************/
    /*      Concentrator-specific provisioning      */
    /************************************************/
    #ifdef PROVISIONING_CONFIG_CONCENTRATOR /* Start Concentrator-specific provisioning */

    /* Provisioning -  LoRaWAN DEV EUI*/
    ret2 += mtd_write(mtd_dev, PROVISIONING_FLASH_DEV_LOWRAWAN_DEV_EUI, 
        PROVISIONING_ADD_TO_BASE_ADDRESS(PROVISIONING_FLASH_ADDRESS_LOWRAWAN_DEV_EUI), 
        sizeof(PROVISIONING_FLASH_DEV_LOWRAWAN_DEV_EUI));
    /* Provisioning - LoRaWAN APP EUI */
    ret2 += mtd_write(mtd_dev, PROVISIONING_FLASH_DEV_LOWRAWAN_APP_EUI, 
        PROVISIONING_ADD_TO_BASE_ADDRESS(PROVISIONING_FLASH_ADDRESS_LOWRAWAN_APP_EUI), 
        PROVISIONING_FLASH_LEN_LOWRAWAN_APP_EUI);

    /* Provisioning - LoRaWAN APP Key */
    ret2 += mtd_write(mtd_dev, PROVISIONING_FLASH_DEV_LOWRAWAN_APP_KEY, 
        PROVISIONING_ADD_TO_BASE_ADDRESS(PROVISIONING_FLASH_ADDRESS_LOWRAWAN_APP_KEY), 
        PROVISIONING_FLASH_LEN_LOWRAWAN_APP_KEY);

    /* Provisioning - Secure Save AES-128 Key */
    ret2 += mtd_write(mtd_dev, PROVISIONING_FLASH_DEV_SEC_SAVE_AES_KEY, 
        PROVISIONING_ADD_TO_BASE_ADDRESS(PROVISIONING_FLASH_ADDRESS_SEC_SAVE_AES_KEY), 
        PROVISIONING_FLASH_LEN_SEC_SAVE_AES_KEY);

    #endif /* End Concentrator-specific provisioning */
    
    if(ret2)
    {
        LOG_ERROR("Failed to write test data to MTD.\n");
    }
    else
    {
        LOG_INFO("Initialized MTD test data with:\n");
        char buf[PROVISIONING_HELPER_BUF_SIZE];
        mtd_read(mtd_dev, buf, PROVISIONING_FLASH_PAGE_BASE_ADDR, PROVISIONING_HELPER_BUF_SIZE);
        od_hex_dump(buf, sizeof(buf), OD_WIDTH_DEFAULT);
    }
}

int provisioning_helper_get_device_id(uint8_t *device_id)
{
    LOG_INFO("Inside provisioning_helper_get_device_id.\n");

    uint8_t page_buf[PROVISIONING_HELPER_BUF_SIZE];
    int ret = mtd_read(mtd_dev, page_buf, PROVISIONING_FLASH_PAGE_BASE_ADDR, PROVISIONING_HELPER_BUF_SIZE);

    if(ret !=0)
    {
        LOG_ERROR("Provisioning helper failed - couldn't read flash memory to access PROVISIONING_FLASH_ADDRESS_SEC_SAVE_AES_KEY.\n");
        LOG_ERROR("Returned: %d\n", ret);
        return -1;
    }

    memcpy(device_id, page_buf + PROVISIONING_FLASH_ADDRESS_DEVICE_ID, PROVISIONING_FLASH_LEN_DEVICE_ID);
    LOG_INFO("Provisioned Device ID is: %x\n", device_id[0]);
    // od_hex_dump(device_id, PROVISIONING_FLASH_LEN_DEVICE_ID, OD_WIDTH_DEFAULT);
    return 0;
}

int provisioning_helper_get_ieee802154_security_key(uint8_t *ieee802154_security_key)
{
     LOG_INFO("Inside provisioning_helper_get_ieee802154_security_key.\n");

    uint8_t page_buf[PROVISIONING_HELPER_BUF_SIZE];
    int ret = mtd_read(mtd_dev, page_buf, PROVISIONING_FLASH_PAGE_BASE_ADDR, PROVISIONING_HELPER_BUF_SIZE);

    if(ret !=0)
    {
        LOG_ERROR("Provisioning helper failed - couldn't read flash memory to access PROVISIONING_FLASH_ADDRESS_SEC_SAVE_AES_KEY.\n");
        LOG_ERROR("Returned: %d\n", ret);
        return -1;
    }

    memcpy(ieee802154_security_key, page_buf + PROVISIONING_FLASH_ADDRESS_IEEE802154_KEY, PROVISIONING_FLASH_LEN_IEEE802154_KEY);
    LOG_INFO("Provisioned IEEE 802.15.4 security key is: %x%x %x%x %x%x %x%x %x%x %x%x %x%x %x%x\n", ieee802154_security_key[0], ieee802154_security_key[1], ieee802154_security_key[2], ieee802154_security_key[3], 
        ieee802154_security_key[4], ieee802154_security_key[5], ieee802154_security_key[6], ieee802154_security_key[7],
        ieee802154_security_key[8], ieee802154_security_key[9], ieee802154_security_key[10], ieee802154_security_key[11],
        ieee802154_security_key[12], ieee802154_security_key[13], ieee802154_security_key[14], ieee802154_security_key[15]);
    // od_hex_dump(device_id, PROVISIONING_FLASH_LEN_DEVICE_ID, OD_WIDTH_DEFAULT);
    return 0;
}
// int provisioning_helper_get_concentrator_ipv6_addr(uint8_t *concentrator_ipv6_addr)
// int provisioning_helper_get_psk_id_key(uint8_t *psk_id, uint8_t *psk_key)
// int provisioning_helper_get_lorawan_cred(uint8_t *lorawan_dev_eui, uint8_t *lorawan_app_eui, uint8_t *lorawan_app_key)

// #ifdef PROVISIONING_CONFIG_CONCENTRATOR /* Start Concentrator-specific provisioning */

int provisioning_helper_get_sec_save_aes_key(uint8_t *sec_save_aes_key)
{
    LOG_INFO("Inside provisioning_helper_get_sec_save_aes_key.\n");

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
    // od_hex_dump(sec_save_aes_key, AES_KEY_SIZE, 0);
    return 0;
}

// #endif /* End Concentrator-specific provisioning */