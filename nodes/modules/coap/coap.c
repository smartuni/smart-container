#include "include/coap.h"

#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "fmt.h"
#include "net/gcoap.h"
#include "net/utils.h"
#include "od.h"

// declare variables
char *coap_path = "/temperature";
char concentrator_ip[IPV6_ADDR_MAX_STR_LEN] = "fe80::ec5d:86f9:88fd:a1dc";
bool coap_response_ok;             //has to be changed, quick and dirty at the moment
bool found_concentrator;        //has to be changed, quick and dirty at the moment

static void _discover_resp_handler(const gcoap_request_memo_t *memo, coap_pkt_t* pdu, const sock_udp_ep_t *remote);
static size_t send_req(char *addr, char *port, char *path, char *data, unsigned method, gcoap_resp_handler_t resp_handler);
static size_t _send(uint8_t *buf, size_t len, char *addr_str, char *port_str, gcoap_resp_handler_t resp_handler);
static bool _parse_endpoint(sock_udp_ep_t *remote, const char *addr_str, const char *port_str);

void send_to_concentrator(char* msg) {
    (void) msg;
    printf("test");
}

size_t discover_concentrator(void){
// function discovers concentrator node and saves its ip    

    ztimer_now_t last_wakeup = ztimer_now(ZTIMER_MSEC);

    puts("Send multicast to discover concentrator");

    // call multicast address via COAP_GET
    if (!send_req("ff02::1", "5683", "/.well-known/core", "0", COAP_GET, _discover_resp_handler)) {//ff02::1 //fe80::fcb2:9130:a6fa:74b3
        puts("multicast send, waiting for response");
    } else {
        puts("multicast failed");
        return 1;
    }
    while(1) {
        puts("Send multicast to discover concentrator");
        // call multicast address via COAP_GET
        if (!send_req("ff02::1", "5683", "/.well-known/core", "0", COAP_GET, _discover_resp_handler)) {//ff02::1 //fe80::fcb2:9130:a6fa:74b3
            puts("multicast send, waiting for response");

        } else {
            puts("multicast failed");
            coap_response_ok = true;
        }
        while(!found_concentrator && !coap_response_ok)                        // has to be changed, quick and dirty at the moment
        coap_response_ok = false;

        if(found_concentrator){
            printf("\nFound concentrator with ipv6: %s\n", concentrator_ip);
            break;
        } else {
            ztimer_periodic_wakeup(ZTIMER_MSEC, &last_wakeup, 5000);
        }
    }
    return 0;
}

void _discover_resp_handler(const gcoap_request_memo_t *memo, coap_pkt_t* pdu, const sock_udp_ep_t *remote)
{
    // specific response handler to discover the concentrator node
     if (memo->state == GCOAP_MEMO_TIMEOUT) {
        printf("Message timeout, trying again\n");
        coap_response_ok = true;
        return;
    }
    else if (memo->state != GCOAP_MEMO_RESP) {
        printf("Error in response, trying again\n");
        coap_response_ok = true;
        return;
    }
    else {
        char ip[IPV6_ADDR_MAX_STR_LEN];
        ipv6_addr_to_str(ip, (ipv6_addr_t *) &remote->addr.ipv6, IPV6_ADDR_MAX_STR_LEN);
        printf("receiver ipv6: %s\n", ip);
        
        if (pdu->payload_len) {
            printf("payload: %s\n", (char *)pdu->payload);
            if (strstr((char *)pdu->payload, coap_path)) {  // found concentrator
                printf("Found device is concentrator!\n");
                found_concentrator = true;
                strcpy( concentrator_ip, ip);

            } else {
                printf("Found device is not concentrator, trying again\n");
                coap_response_ok = true;
            }
        } else {
            printf("Empty payload, trying again\n");
            coap_response_ok = true;
        }
    }
    printf("\n\n");
}

size_t send_req(char *addr, char *port, char *path, char *data, unsigned method, gcoap_resp_handler_t resp_handler)
{
    uint8_t buf[CONFIG_GCOAP_PDU_BUF_SIZE];
    coap_pkt_t pdu;
    size_t len;

    size_t data_len = strlen(data);

    if(data != NULL) {
        /* initialize the CoAP request */
        gcoap_req_init(&pdu, buf, CONFIG_GCOAP_PDU_BUF_SIZE, method, path);

        /* send a confirmable message */
        coap_hdr_set_type(pdu.hdr, COAP_TYPE_CON);

        /* specify the plain text format and copy the payload */                                                               // wir senden nur mit payload -> überprüfung überflüssig/früher möglich
        coap_opt_add_format(&pdu, COAP_FORMAT_TEXT);

        len = coap_opt_finish(&pdu, COAP_OPT_FINISH_PAYLOAD);
        if (pdu.payload_len >= data_len) {
            memcpy(pdu.payload, data, data_len);
            len += data_len;
        }
        else {
            puts("The buffer is too small, reduce the message length");
            return -1;
        }

        printf("gcoap_cli: sending msg ID %u, %u bytes\n", coap_get_id(&pdu), (unsigned) len);
        if (!_send(buf, len, addr, port, resp_handler)) {
            puts("gcoap_cli: msg send failed");
            return -1;
        }
    } else {
        puts("No payload");
        return -1;
    }
    return 0;
}

size_t _send(uint8_t *buf, size_t len, char *addr_str, char *port_str, gcoap_resp_handler_t resp_handler)
{
    size_t bytes_sent;
    sock_udp_ep_t remote;

    if (!_parse_endpoint(&remote, addr_str, port_str)) {
        return 0;
    }
    bytes_sent = gcoap_req_send(buf, len, &remote, resp_handler, NULL);
    if (bytes_sent > 0) {
        //req_count++;
    }
    return bytes_sent;
}

bool _parse_endpoint(sock_udp_ep_t *remote, const char *addr_str, const char *port_str)
{
    netif_t *netif;

    /* parse hostname */
    if (netutils_get_ipv6((ipv6_addr_t *)&remote->addr, &netif, addr_str) < 0) {
        puts("gcoap_cli: unable to parse destination address");
        return false;
    }
    remote->netif = netif ? netif_get_id(netif) : SOCK_ADDR_ANY_NETIF;
    remote->family = AF_INET6;

    /* parse port */
    remote->port = atoi(port_str);
    if (remote->port == 0) {
        puts("gcoap_cli: unable to parse destination port");
        return false;
    }

    return true;
}