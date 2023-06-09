/* coap specific code*/

// include libraries
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fmt.h"
#include "net/gcoap.h"
#include "net/utils.h"
#include "od.h"

// declare variables
#define WAIT_TIME 5000
extern char *coap_path;

char concentrator_ip[IPV6_ADDR_MAX_STR_LEN];
bool coap_response_ok = false;              //has to be changed, quick and dirty at the moment
bool found_concentrator = false;            //has to be changed, quick and dirty at the moment


static void _std_resp_handler(const gcoap_request_memo_t *memo, coap_pkt_t* pdu,
                          const sock_udp_ep_t *remote)
{
    // standard response handler
    (void)remote;       // not interested in the source currently

    if (memo->state == GCOAP_MEMO_TIMEOUT) {
        printf("gcoap: timeout for msg ID %02u\n", coap_get_id(pdu));
        return;
    }
    else if (memo->state != GCOAP_MEMO_RESP) {
        printf("gcoap: error in response\n");
        printf("state: %d\n", memo->state);
        return;
    }

    char *class_str = (coap_get_code_class(pdu) == COAP_CLASS_SUCCESS) ? "Success" : "Error";

    printf("gcoap: response %s, code %1u.%02u", class_str,
                                                coap_get_code_class(pdu),
                                                coap_get_code_detail(pdu));
    if (pdu->payload_len) {
        unsigned content_type = coap_get_content_type(pdu);
        if (content_type == COAP_FORMAT_TEXT
                || content_type == COAP_FORMAT_LINK
                || coap_get_code_class(pdu) == COAP_CLASS_CLIENT_FAILURE
                || coap_get_code_class(pdu) == COAP_CLASS_SERVER_FAILURE) {
            // Expecting diagnostic payload in failure cases 
            printf(", %u bytes\n%.*s\n", pdu->payload_len, pdu->payload_len,
                                                          (char *)pdu->payload);
        }
        else {
            printf(", %u bytes\n", pdu->payload_len);
            od_hex_dump(pdu->payload, pdu->payload_len, OD_WIDTH_DEFAULT);
        }
    }
    else {
        printf(", empty payload\n");
    }
}

static void _discover_resp_handler(const gcoap_request_memo_t *memo, coap_pkt_t* pdu,
                          const sock_udp_ep_t *remote)
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
                strcpy( concentrator_ip, ip);
                found_concentrator = true;
                coap_response_ok = true;
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

static bool _parse_endpoint(sock_udp_ep_t *remote,
                            const char *addr_str, const char *port_str)
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

static size_t _send(uint8_t *buf, size_t len, char *addr_str, char *port_str, gcoap_resp_handler_t resp_handler)
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

static size_t send_req(char *addr, char *port, char *path, char *data, unsigned method, gcoap_resp_handler_t resp_handler)
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

static size_t discover_concentrator(void){
// function discovers concentrator node and saves its ip    

    ztimer_now_t last_wakeup = ztimer_now(ZTIMER_MSEC);

    while(1) {
        puts("Send multicast to discover concentrator");

        // call multicast address via COAP_GET
        if (!send_req("ff02::1", "5683", "/.well-known/core", "0", COAP_GET, _discover_resp_handler)) {
            puts("multicast send, waiting for response");
        } else {
            puts("multicast failed");
            coap_response_ok = true;        // set true to skip loop
            ztimer_periodic_wakeup(ZTIMER_MSEC, &last_wakeup, WAIT_TIME);
        }
        while(!coap_response_ok) {
            ztimer_periodic_wakeup(ZTIMER_MSEC, &last_wakeup, WAIT_TIME);
        }
        coap_response_ok = false;

        if(found_concentrator) {
            printf("\nFound concentrator with ipv6: %s\n", concentrator_ip);
            break;
        }
        ztimer_periodic_wakeup(ZTIMER_MSEC, &last_wakeup, WAIT_TIME);
    }
    return 0;
}