#ifndef CREDMAN_HELPER_H
#define CREDMAN_HELPER_H

#include "mtd.h"
#include "mtd_flashpage.h"

#define AES_KEY_SIZE 16

/* Provisioning - Flash Page Number */
#define CREDMAN_FLASH_PAGE_NUMBER 240
#define CREDMAN_FLASH_PAGE_START_ADDR (uint32_t)((uintptr_t)flashpage_addr(CREDMAN_FLASH_PAGE_NUMBER))
#define CREDMAN_ADDRESS(addr) ((uint32_t) (CREDMAN_FLASH_PAGE_START_ADDR + addr))

/* Provisioning - Device ID */
#define CREDMAN_FLASH_ADDRESS_DEVICE_ID 0x00
#define CREDMAN_FLASH_LEN_DEVICE_ID 1

/* Provisioning - IEEE 802.15.4 Key */
#define CREDMAN_FLASH_ADDRESS_IEEE802154_KEY 0x01
#define CREDMAN_FLASH_LEN_IEEE802154_KEY 16

/* Provisioning - Concentrator node IPv6 addresss */
#define CREDMAN_FLASH_ADDRESS_CONCENTRATOR_IPV6_ADDR 0x11
#define CREDMAN_FLASH_LEN_PSK_KEY 16

/* Provisioning - DTLS PSK AES128 Key*/
#define CREDMAN_FLASH_ADDRESS_DTLS_PSK_AES_KEY 0x21
#define CREDMAN_FLASH_LEN_DTLS_PSK_AES_KEY 16

/************************************************/
/*      Concentrator-specific provisioning      */
/************************************************/
#if(CREDMAN_CONFIG_CONCENTRATOR) /* Start Concentrator-specific provisioning */

/* Provisioning -  LoRaWAN DEV EUI*/
#define CREDMAN_FLASH_ADDRESS_LOWRAWAN_DEV_EUI 0x31
#define CREDMAN_FLASH_LEN_LOWRAWAN_DEV_EUI 16

/* Provisioning - LoRaWAN APP EUI */
#define CREDMAN_FLASH_ADDRESS_LOWRAWAN_APP_EUI 0x41
#define CREDMAN_FLASH_LEN_LOWRAWAN_APP_EUI 16

/* Provisioning - LoRaWAN APP Key */
#define CREDMAN_FLASH_ADDRESS_LOWRAWAN_APP_EUI 0x51
#define CREDMAN_FLASH_LEN_LOWRAWAN_APP_EUI 32

/* Provisioning - Secure Save AES-128 Key */
#define CREDMAN_FLASH_ADDRESS_SEC_SAVE_AES_KEY 0x71
#define CREDMAN_FLASH_LEN_SEC_SAVE_AES_KEY 16

#endif /* End Concentrator-specific provisioning */

int init_provisioning(mtd_dev_t *mtd_dev);
int read_psk(mtd_dev_t *mtd_dev, uint8_t *psk_id, uint8_t *psk_key);

#endif /* CREDMAN_HELPER_H */
/** @} */

// /* Provisioning - */
// #define CREDMAN_FLASH_
// #define CREDMAN_FLASH_LEN_