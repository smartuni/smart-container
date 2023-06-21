/* * Copyright (C) 2020 Freie Universität Berlin *               2020 HAW Hamburg * * This file is subject to the terms and conditions of the GNU Lesser * General Public License v2.1. See the file LICENSE in the top level * directory for more details. */ /** * @brief       LoRaWAN Sensor Application * * @author      Akshai M    <akshai.m@fu-berlin.de> * @author      José Alamos <jose.alamos@haw-hamburg.de> * */
#include <stdio.h> 
#include "board.h" /* Board PIN definitions */
#include "periph/gpio.h" /* Periph GPIO */
#include "event.h" /* Event Queues and Event Thread */
#include "event/thread.h"
#include "net/gnrc/netif.h" /* GNRC's network interfaces */
#include "net/gnrc/netif/hdr.h" /* GNRC's network communication interface */
#include "net/gnrc/netapi.h" 
#include "clist.h"
#include "od.h"
#include "fmt.h" /* String formatting */
#include "senml/cbor.h"
#include "concentrator_lorawan.h"

#define JOIN_DELAY (10U * MS_PER_SEC) /* Unit system wait time to complete join procedure in seconds */
#define LORAWAN_DATARATE LORAMAC_DR_2 /* Delay between transmission in milliseconds */
#define TRANSMISSION_INTERVAL (15U * MS_PER_SEC)
static gnrc_netif_t *lorawan_netif;                                                                                                                                                                                                                            /* Number of times the button has been pressed */
static uint8_t counter;                                                                                                                                                                                                                                        /* [TASK 2: Set the DevEUI, AppEUI and AppKey] */
char deveui_str[] = "70B3D57ED005D96E";
char appeui_str[] = "848A86E1F3DAD4C8";
char appkey_str[] = "E336278BE70BFF784DD752DF18231D9B"; /* Button callback */
void button_callback(void* arg)
{
    (void)arg; /* Not used */
    puts("Button pressed");
    counter++;
}
 /* Join the network */
void activate(gnrc_netif_t *netif)
{ /* All values are shorter than the APPKEY length */
    lorawan_netif = netif;
    uint8_t key_holder[LORAMAC_APPKEY_LEN];
    int size;
    printf("Joining the LoRaWAN network (%d)\n", netif->pid);
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
        // printf("%p\n", dev);
        gnrc_netapi_get(dev->pid, NETOPT_DEVICE_TYPE, 0, (void *)&type, sizeof(type));
        if (type == NETDEV_TYPE_LORA) {
            printf("Found lora interface %d\n", dev->pid);
            return dev;
        }
    } /* Shouldn't happen in this exercise */
    return NULL;
}

void sendData(uint8_t *data, size_t len){
    gnrc_pktsnip_t *pkt, *hdr;
    uint8_t port = CONFIG_LORAMAC_DEFAULT_TX_PORT; /* Default: 2 */               /* [TASK 3: Allocate a packet snip for the counter data] */
    pkt = gnrc_pktbuf_add(NULL, (void *)&data, len, GNRC_NETTYPE_UNDEF); /* [TASK 3: Build GNRC Netif Header snip and prepend to packet] */
    printf("added pkt data \n");
    hdr = gnrc_netif_hdr_build(NULL, 0, &port, sizeof(port));
    printf("added hdr\n");
    pkt = gnrc_pkt_prepend(pkt, hdr);                                         /* [TASK 3: Send packet using GNRC NetAPI] */
    printf("prepended hdr to pkt\n");
    gnrc_netapi_send(lorawan_netif->pid, pkt);
    puts("Successfully sent packet");
    ztimer_sleep(ZTIMER_MSEC, TRANSMISSION_INTERVAL);
    printf("Die Funktion wurde aufgerufen");
}

#define BUF_SIZE (128)
static uint8_t cbor_buf[BUF_SIZE];

void _encode_list_member(nanocbor_encoder_t *enc, clist_node_t *data)
{
    cycling_buffer *element = (cycling_buffer *)data;

    switch (element->sensor_type) {
    case SENSOR_TYPE_CRASH: 
    {
        senml_bool_value_t vf = {0};
        vf.attr.base_name = "crash";
        vf.attr.time = senml_duration_s(element->timestamp);
        vf.value = element->values.event;
        senml_encode_bool_cbor(enc, &vf);
        break;
    }
    case SENSOR_TYPE_HUMIDITY: 
    {
        senml_value_t vf = {
            .attr = {
                .base_name = "hum",
                .time = senml_duration_s(element->timestamp)
            },
            .value = senml_uint(61)
        };
        senml_encode_value_cbor(enc, &vf);
        break;
    }
    case SENSOR_TYPE_GPS:
    {
        size_t string_len = strlen(element->values.gps);
        senml_string_value_t vs = {
            .attr = {
                .time = senml_duration_s(6),
                .base_name = "gps"
            },
            .value = element->values.gps,
            .len = string_len
        };
        senml_encode_string_cbor(enc, &vs);
        break;
    }
    default:
        break;
    }
}

/*
a test that works

    cycling_buffer crash_data = {
        .next = NULL,
        .sensor_type = SENSOR_TYPE_CRASH,
        .values.event = true,
        .timestamp = 1,
    };


    cycling_buffer hum_data = {
        .next = NULL,
        .sensor_type = SENSOR_TYPE_HUMIDITY,
        .values.value = 50,
        .timestamp = 2,
    };

    cycling_buffer gps_data = {
        .next = NULL,
        .sensor_type = SENSOR_TYPE_GPS,
        .values.gps = "1234.5678,1234.5678",
        .timestamp = 3,
    };

    clist_node_t my_list = {0};
    clist_rpush(&my_list, (clist_node_t *)&crash_data);
    clist_rpush(&my_list, (clist_node_t *)&hum_data);
    clist_rpush(&my_list, (clist_node_t *)&gps_data);

    send_data_list(&my_list);
*/

void send_data_list(clist_node_t *list)
{
    nanocbor_encoder_t enc;

    size_t list_length = clist_count(list);

    memset(cbor_buf, 0, sizeof cbor_buf);
    nanocbor_encoder_init(&enc, cbor_buf, sizeof cbor_buf);

    nanocbor_fmt_array(&enc, list_length);

    clist_node_t *node = list->next;
    do {
        _encode_list_member(&enc, node);
        node = node->next;
    }
    while (node != list->next);

    size_t encoded_length = nanocbor_encoded_len(&enc);

    // od_hex_dump(cbor_buf, encoded_length, 0);
    /* TODO: send the data here */
    // send_data(cbor_buf, encoded_length);
}