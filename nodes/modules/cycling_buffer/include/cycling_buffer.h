#ifndef CYCLING_BUFFER_H
#define CYCLING_BUFFER_H

#include <clist.h>
#include <stdint.h>

#define CYCLING_BUFFER_SIZE 30
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
    clist_node_t node;
    sensor_types sensor_type;
    union values {
        bool event;
        int value;
        char gps[GPS_BUFF];
    } vals;
    int timestamp;
} sensor_data_entry;

void initCyclingBuffer(void);
sensor_data_entry* getCyclingBufferSlot(void);
clist_node_t* getCyclingBuffer(void);
void clearCyclingBuffer(void);



#endif
