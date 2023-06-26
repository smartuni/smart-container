#include "include/cycling_buffer.h"
#include "stdio.h"
#include <memarray.h>
#include <kernel_defines.h>

#define MIN_STRING_BUFF_SIZE GPS_BUFF + 128

static const char string_format[] = "sensor_type: %s, value: %s, timestamp: %d;\n";

static memarray_t memmanage;
static uint8_t mempool[CYCLING_BUFFER_SIZE * sizeof(sensor_data_entry)];
static clist_node_t cycling_buffer_head = {0};

void initCyclingBuffer(void) {
    memarray_init(&memmanage, mempool, sizeof(sensor_data_entry), CYCLING_BUFFER_SIZE);
}

sensor_data_entry* getCyclingBufferSlot(void) {
    sensor_data_entry* elem = memarray_calloc(&memmanage);
    if(elem) clist_rpush(&cycling_buffer_head, &elem->node);
    return elem;
}

clist_node_t* getCyclingBuffer(void) {
    return &cycling_buffer_head;
}

void clearCyclingBuffer(void) {
    clist_node_t *next;
    while((next = clist_lpop(&cycling_buffer_head)) != NULL) {
        sensor_data_entry* elem = container_of(next, sensor_data_entry, node);
        memarray_free(&memmanage, elem);
    }
}

void sensorDataToString(char* buff, size_t buffsize, sensor_data_entry* data) {
    char sensor_type[6];
    char value[GPS_BUFF];
    int timestamp = 0;
    switch(data->sensor_type) {
        case SENSOR_TYPE_CRASH:
            snprintf(sensor_type, 6, "crash");
            snprintf(value, GPS_BUFF, "%s", data->vals.event ? "true" : "false");
            timestamp = data->timestamp;
            break;
        case SENSOR_TYPE_HUMIDITY:
            snprintf(sensor_type, 6, "hum");
            snprintf(value, GPS_BUFF, "%d", data->vals.value);
            timestamp = data->timestamp;
            break;
        case SENSOR_TYPE_TEMPERATURE:
            snprintf(sensor_type, 6, "temp");
            snprintf(value, GPS_BUFF, "%d", data->vals.value);
            timestamp = data->timestamp;
            break;
        case SENSOR_TYPE_WATERLEAK:
            snprintf(sensor_type, 6, "leak");
            snprintf(value, GPS_BUFF, "%s", data->vals.event ? "true" : "false");
            timestamp = data->timestamp;
            break;
        case SENSOR_TYPE_DOOR:
            snprintf(sensor_type, 6, "door");
            snprintf(value, GPS_BUFF, "%s", data->vals.event ? "true" : "false");
            timestamp = data->timestamp;
            break;
        case SENSOR_TYPE_GPS:
            snprintf(sensor_type, 6, "gps");
            snprintf(value, GPS_BUFF, "%s", data->vals.gps);
            timestamp = data->timestamp;
            break;
        default:
            break;
    }


     snprintf(buff, buffsize, string_format, sensor_type, value, timestamp);
}