/*
 * Copyright (C) 2014 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     examples
 * @{
 *
 * @file
 * @brief       Hello World application
 *
 * @author      Kaspar Schleiser <kaspar@schleiser.de>
 * @author      Ludwig Knüpfer <ludwig.knuepfer@fu-berlin.de>
 *
 * @}
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <kernel_defines.h>

#include <clist.h>
#include <memarray.h>

#define GPS_BUFF 128
#define CYCLING_BUFFER_SIZE 30

typedef enum {
    SENSOR_TYPE_CRASH,
    SENSOR_TYPE_HUMIDITY,
    SENSOR_TYPE_TEMPERATURE,
    SENSOR_TYPE_WATERLEAK,
    SENSOR_TYPE_DOOR,
    SENSOR_TYPE_GPS,
} sensor_types;

typedef struct {
    clist_node_t node;
    sensor_types sensor_type;
    union values {
        bool event;
        int value;
        char gps[GPS_BUFF];
    } vals;
    int timestamp;
} sensor_data_entry;

memarray_t memmanage;
uint8_t mempool[CYCLING_BUFFER_SIZE * sizeof(sensor_data_entry)];

int main(void)
{
    puts("Hello World!");

    printf("You are running RIOT on a(n) %s board.\n", RIOT_BOARD);
    printf("This board features a(n) %s MCU.\n", RIOT_MCU);

    memarray_init(&memmanage, mempool, sizeof(sensor_data_entry), CYCLING_BUFFER_SIZE);

    clist_node_t list = {0}; /* clear list */
    clist_node_t *curr_el;
    sensor_data_entry* el1 = memarray_alloc(&memmanage);
    el1->sensor_type = SENSOR_TYPE_DOOR;
    /* Add element to list */
    clist_rpush(&list, &el1->node);
    /* Add second element to the list */
    sensor_data_entry el2 = {.sensor_type = SENSOR_TYPE_HUMIDITY};
    clist_rpush(&list, &el2.node);
    /* Pop the first element */
    curr_el = clist_lpop(&list);
    /* Cast the element to the list structure*/
    sensor_data_entry *cast_el = container_of(curr_el, sensor_data_entry, node);
    printf("%d", cast_el->sensor_type);
    /* Pop second element */
    curr_el = clist_lpop(&list);
    cast_el = container_of(curr_el, sensor_data_entry, node);
    printf("%d", cast_el->sensor_type);

    (void) curr_el;
    /* The queue is now empty. Trying to pop more elements should return NULL */
    assert(clist_lpop(&list) == NULL);
    




    return 0;
}
