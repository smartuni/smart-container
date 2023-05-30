#include "include/coap.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "fmt.h"
#include "net/gcoap.h"
#include "net/utils.h"
#include "od.h"

void send_to_concentrator(const char* msg) {
    //send_req("fe80::fcb2:9130:a6fa:74b3", "5683", coap_path, sensor_data, COAP_POST);
    printf("send msg to %s: %s\n", CONCENTRATOR_IP, msg);
}
