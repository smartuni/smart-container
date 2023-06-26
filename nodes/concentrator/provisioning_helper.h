#ifndef PROVISIONING_HELPER_H
#define PROVISIONING_HELPER_H

#include "log.h"
#include "od.h"
#include "random.h"
#include "mtd.h"
#include "mtd_flashpage.h"

// #define PROVISIONING_CONFIG_CONCENTRATOR 
// #define PROVISIONING_ENABLE_DEV 1

#define AES_KEY_SIZE 16
#define AES_BLOCK_SIZE 16

/* Provisioning - Flash Page Number */
#define PROVISIONING_FLASH_PAGE_NUMBER 240
#define PROVISIONING_FLASH_PAGE_BASE_ADDR (uint32_t)((uintptr_t)flashpage_addr(PROVISIONING_FLASH_PAGE_NUMBER))
#define PROVISIONING_ADD_TO_BASE_ADDRESS(addr) (uint32_t)(PROVISIONING_FLASH_PAGE_BASE_ADDR + addr)

/* Provisioning - Device ID */
#define PROVISIONING_FLASH_ADDRESS_DEVICE_ID 0x00
#define PROVISIONING_FLASH_LEN_DEVICE_ID 1

/* Provisioning - IEEE 802.15.4 Key */
#define PROVISIONING_FLASH_ADDRESS_IEEE802154_KEY 0x01
#define PROVISIONING_FLASH_LEN_IEEE802154_KEY 16

/* Provisioning - Concentrator node IPv6 addresss */
#define PROVISIONING_FLASH_ADDRESS_CONCENTRATOR_IPV6_ADDR 0x11
#define PROVISIONING_FLASH_LEN_CONCENTRATOR_IPV6_ADDR 16

/* Provisioning - DTLS PSK AES128 Key*/
#define PROVISIONING_FLASH_ADDRESS_DTLS_PSK_AES_KEY 0x21
#define PROVISIONING_FLASH_LEN_DTLS_PSK_AES_KEY 16

/************************************************/
/*      Concentrator-specific provisioning      */
/************************************************/
#ifdef PROVISIONING_CONFIG_CONCENTRATOR /* Start Concentrator-specific provisioning */

/* Provisioning -  LoRaWAN DEV EUI*/
#define PROVISIONING_FLASH_ADDRESS_LOWRAWAN_DEV_EUI 0x31
#define PROVISIONING_FLASH_LEN_LOWRAWAN_DEV_EUI 16

/* Provisioning - LoRaWAN APP EUI */
#define PROVISIONING_FLASH_ADDRESS_LOWRAWAN_APP_EUI 0x41
#define PROVISIONING_FLASH_LEN_LOWRAWAN_APP_EUI 16

/* Provisioning - LoRaWAN APP Key */
#define PROVISIONING_FLASH_ADDRESS_LOWRAWAN_APP_KEY 0x51
#define PROVISIONING_FLASH_LEN_LOWRAWAN_APP_KEY 32

/* Provisioning - Secure Save AES-128 Key */
#define PROVISIONING_FLASH_ADDRESS_SEC_SAVE_AES_KEY 0x71
#define PROVISIONING_FLASH_LEN_SEC_SAVE_AES_KEY 16

#endif /* End Concentrator-specific provisioning */

#if(PROVISIONING_ENABLE_DEV==1)
    #include "provisioning_helper_dev.h"
#endif

int provisioning_helper_init(void);
void provisioning_helper_init_dev(void);
int provisioning_helper_get_device_id(uint8_t *device_id);
int provisioning_helper_get_ieee802154_security_key(uint8_t *ieee802154_security_key);
int provisioning_helper_get_concentrator_ipv6_addr(uint8_t *concentrator_ipv6_addr);
int provisioning_helper_get_psk_id_key(uint8_t *psk_id, uint8_t *psk_key);
int provisioning_helper_get_lorawan_cred(uint8_t *lorawan_dev_eui, uint8_t *lorawan_app_eui, uint8_t *lorawan_app_key);
int provisioning_helper_get_sec_save_aes_key(uint8_t *sec_save_aes_key);

#endif // PROVISIONING_HELPER_H