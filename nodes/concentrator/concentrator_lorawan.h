#ifndef CONCENTRATOR_LORAWAN_H
#define CONCENTRATOR_LORAWAN_H

#include "net/lora.h"  /* LoRa defines */ 
#include "net/gnrc/netif.h" /* GNRC's network interfaces */


/*
#define GPS_BUFF 128
typedef enum {
    SENSOR_TYPE_CRASH,
    SENSOR_TYPE_HUMIDITY,
    SENSOR_TYPE_TEMPERATURE,
    SENSOR_TYPE_WATERLEAK,
    SENSOR_TYPE_DOOR,
    SENSOR_TYPE_GPS,
} sensor_types;

typedef struct {
    clist_node_t* next;
    sensor_types sensor_type;
    int timestamp;
    union v {
        bool event;
        int value;
        char gps[GPS_BUFF];
    } values;
} sensor_data_entry;*/

gnrc_netif_t *get_lorawan_netif(void);
void button_callback(void* arg);
void activate(gnrc_netif_t *netif);
void send_data(uint8_t *data, size_t len);

void send_data_list(clist_node_t *list);

#endif /* CONCENTRATOR_LORAWAN_H */
