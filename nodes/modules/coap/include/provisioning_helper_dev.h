#ifndef PROVISIONING_HELPER_DEV_H
#define PROVISIONING_HELPER_DEV_H

/* Provisioning - Device ID */
#define PROVISIONING_FLASH_DEV_DEVICE_ID "1"

/* Provisioning - IEEE 802.15.4 Key */
#define PROVISIONING_FLASH_DEV_IEEE802154_KEY "29DJ29XL8D3Q7QXG"

/* Provisioning - Concentrator node IPv6 addresss */
#define PROVISIONING_FLASH_DEV_CONCENTRATOR_IPV6_ADDR "FCOVNHRH661MK9P3"

/* Provisioning - DTLS PSK AES128 Key*/
#define PROVISIONING_FLASH_DEV_DTLS_PSK_AES_KEY "UALO5GO0LZFNLEG9"

/************************************************/
/*      Concentrator-specific provisioning      */
/************************************************/
#ifdef PROVISIONING_CONFIG_CONCENTRATOR /* Start Concentrator-specific provisioning */

/* Provisioning -  LoRaWAN DEV EUI*/
#define PROVISIONING_FLASH_DEV_LOWRAWAN_DEV_EUI "IX264ODJ0WI46ACK"

/* Provisioning - LoRaWAN APP EUI */
#define PROVISIONING_FLASH_DEV_LOWRAWAN_APP_EUI "EFNOV8PRA2QWTSYB"

/* Provisioning - LoRaWAN APP Key */
#define PROVISIONING_FLASH_DEV_LOWRAWAN_APP_KEY "1R7RMYP0Z8M5X27WMQAYLIUPO90DB4EZ"

/* Provisioning - Secure Save AES-128 Key */
#define PROVISIONING_FLASH_DEV_SEC_SAVE_AES_KEY "4HC4LV2PAM58B2OW"

#endif /* End Concentrator-specific provisioning */

#endif // PROVISIONING_HELPER_DEV_H