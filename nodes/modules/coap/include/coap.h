#ifndef _NODES_COAP_H
#define _NODES_COAP_H

#include "fmt.h"
#include "net/gcoap.h"
#include "net/utils.h"
#include "od.h"

#define CONCENTRATOR_IP "fe80::ec5d:86f9:88fd:a1dc" // "fe80::fcb2:9130:a6fa:74b3"

void server_init(void);
size_t send_req(char *addr, char *port, char *path, char *data, unsigned method);
void send_to_concentrator(char* msg);

#endif