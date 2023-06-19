#ifndef _GPS_H
#define _GPS_H

#include "fmt.h"
#include "minmea.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mutex.h"

#define GPS_SEND_INTERVAL_SEC 300
#define GPS_POLL_INTERVAL_SEC 5

extern bool gpsDataValid;

void handle_gps_msg(char *_str);

#endif