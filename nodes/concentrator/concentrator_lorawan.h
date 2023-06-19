#ifndef CONCENTRATOR_LORAWAN_H
#define CONCENTRATOR_LORAWAN_H

#include "net/lora.h"  /* LoRa defines */ 
#include "net/gnrc/netif.h" /* GNRC's network interfaces */

gnrc_netif_t *get_lorawan_netif(void);
void button_callback(void* arg);
void activate(gnrc_netif_t *netif);
void sendData(uint8_t data);

#endif /* CONCENTRATOR_LORAWAN_H */
