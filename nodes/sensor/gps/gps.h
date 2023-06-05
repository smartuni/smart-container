#ifndef _GPS_H
#define _GPS_H

#include "fmt.h"
#include "minmea.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mutex.h"

void handle_gps_msg(const char *_str);

#endif