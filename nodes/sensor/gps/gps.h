#ifndef _GPS_H
#define _GPS_H

#include "fmt.h"
#include "minmea.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_gps_string(const char *_str);

#endif