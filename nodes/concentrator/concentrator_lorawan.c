/* * Copyright (C) 2020 Freie Universität Berlin *               2020 HAW Hamburg * * This file is subject to the terms and conditions of the GNU Lesser * General Public License v2.1. See the file LICENSE in the top level * directory for more details. */ /** * @brief       LoRaWAN Sensor Application * * @author      Akshai M    <akshai.m@fu-berlin.de> * @author      José Alamos <jose.alamos@haw-hamburg.de> * */
#include <stdio.h> 
#include "board.h" /* Board PIN definitions */
#include "periph/gpio.h" /* Periph GPIO */
#include "event.h" /* Event Queues and Event Thread */
#include "event/thread.h"
#include "net/lora.h"  /* LoRa defines */ 
#include "net/gnrc/netif.h" /* GNRC's network interfaces */
#include "net/gnrc/netif/hdr.h" /* GNRC's network communication interface */
#include "net/gnrc/netapi.h" /* String formatting */ 
#include "fmt.h" 

#define JOIN_DELAY (10U * MS_PER_SEC) /* Unit system wait time to complete join procedure in seconds */
#define LORAWAN_DATARATE LORAMAC_DR_3 /* Delay between transmission in milliseconds */
#define TRANSMISSION_INTERVAL (116U * MS_PER_SEC)
                                                                                                                                                                                                                 /* LoRaWAN netif */
static gnrc_netif_t *lorawan_netif;                                                                                                                                                                                                                            /* Number of times the button has been pressed */
static uint8_t counter;                                                                                                                                                                                                                                        /* [TASK 2: Set the DevEUI, AppEUI and AppKey] */
char deveui_str[] = "70B3D57ED005D96E";
char appeui_str[] = "848A86E1F3DAD4C8";
char appkey_str[] = "E336278BE70BFF784DD752DF18231D9B"; /* Button callback */
static void button_callback(void *arg)
{
    (void)arg; /* Not used */
    puts("Button pressed");
    counter++;
}
 /* Join the network */
static void _activate(gnrc_netif_t *netif)
{ /* All values are shorter than the APPKEY length */
    uint8_t key_holder[LORAMAC_APPKEY_LEN];
    int size;
    puts("Joining the LoRaWAN network");
    size = fmt_hex_bytes(key_holder, appeui_str); /* The key_holder variable holds at this point the AppEUI (`size` bytes) */ /* [TASK 2: Set the AppEUI using GNRC NetAPI] */
    gnrc_netapi_set(netif->pid, NETOPT_LORAWAN_APPEUI, 0, (void *)key_holder, size);
    size = fmt_hex_bytes(key_holder, appkey_str); /* The key_holder variable holds at this point the AppKey (`size` bytes) */ /* [TASK 2: Set the AppKey using GNRC NetAPI] */
    gnrc_netapi_set(netif->pid, NETOPT_LORAWAN_APPKEY, 0, (void *)key_holder, size);
    size = fmt_hex_bytes(key_holder, deveui_str); /* The key_holder variable holds at this point the DevEUI (`size` bytes) */ /* [TASK 2: Set the DevEUI using GNRC NetAPI] */
    gnrc_netapi_set(netif->pid, NETOPT_ADDRESS_LONG, 0, (void *)key_holder, size);
    netopt_enable_t en = NETOPT_ENABLE; /* [TASK 2: Enable OTAA activation] */
    gnrc_netapi_set(netif->pid, NETOPT_OTAA, 0, (void *)&en, sizeof(en));
    en = NETOPT_DISABLE; /* [TASK 2: Disable confirmed transmissions] */
    gnrc_netapi_set(netif->pid, NETOPT_ACK_REQ, 0, (void *)&en, sizeof(en));
    uint8_t dr = LORAWAN_DATARATE; /* [TASK 2: Set Datarate] */
    gnrc_netapi_set(netif->pid, NETOPT_LORAWAN_DR, 0, (void *)&dr, sizeof(dr));
    while (true)
    {
        en = NETOPT_ENABLE;                                                   /* [TASK 2: Use GNRC NetAPI to set the NETOPT_LINK netopt] */
        gnrc_netapi_set(netif->pid, NETOPT_LINK, 0, (void *)&en, sizeof(en)); /* Wait for some seconds and ask the interface if it joined properly */
        ztimer_sleep(ZTIMER_MSEC, JOIN_DELAY);                                /* [TASK 2: Get the activation status into the `en` variable using GNRC         * NetAPI with the NETOPT_LINK netopt] */
        gnrc_netapi_get(netif->pid, NETOPT_LINK, 0, (void *)&en, sizeof(en));
        if (en == NETOPT_ENABLE)
        {
            puts("Device joined");
            break;
        }
        puts("Join failed. Retry");
    }
}
gnrc_netif_t *get_lorawan_netif(void)
{ /* [TASK 1: Use gnrc_netif_iter to iterate all network interface] */
    for (gnrc_netif_t *dev = gnrc_netif_iter(NULL); dev != NULL; dev = gnrc_netif_iter(dev))
    { /* [TASK 1: Get device type and return netif if type is NETDEV_TYPE_LORA] */
        uint16_t type = 0;
        printf("%p", dev);
        gnrc_netapi_get(dev->pid, NETOPT_DEVICE_TYPE, 0, (void *)&type, sizeof(type));
        if (type == NETDEV_TYPE_LORA)
            return dev;
    } /* Shouldn't happen in this exercise */
    return NULL;
}

static void sendData(uint8_t data){
    gnrc_pktsnip_t *pkt, *hdr;
    printf("Counter value is %i\n", data);
    uint8_t port = CONFIG_LORAMAC_DEFAULT_TX_PORT; /* Default: 2 */               /* [TASK 3: Allocate a packet snip for the counter data] */
    pkt = gnrc_pktbuf_add(NULL, (void *)&data, sizeof(data), GNRC_NETTYPE_UNDEF); /* [TASK 3: Build GNRC Netif Header snip and prepend to packet] */
    hdr = gnrc_netif_hdr_build(NULL, 0, &port, sizeof(port));
    pkt = gnrc_pkt_prepend(pkt, hdr);                                         /* [TASK 3: Send packet using GNRC NetAPI] */
    gnrc_netapi_send(lorawan_netif->pid, pkt);
    puts("Successfully sent packet");
    ztimer_sleep(ZTIMER_MSEC, TRANSMISSION_INTERVAL);
    printf("Die Funktion wurde aufgerufen");
}

int main(void)
{
    puts("LoRaWAN Sensor application"); /* Setup button callback */
    if (gpio_init_int(BTN0_PIN, BTN0_MODE, GPIO_FALLING, button_callback, NULL) < 0)
    {
        puts("[FAILED] init BTN0!");
        return 1;
    } /* Try to get a LoRaWAN interface */
    if (!(lorawan_netif = get_lorawan_netif()))
    {
        puts("Couldn't find a LoRaWAN interface");
        return 1;
    }
    _activate(lorawan_netif);
    sendData(2);
    return 0;
}