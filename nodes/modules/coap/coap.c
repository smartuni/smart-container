#include "include/coap.h"

#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "fmt.h"
#include "net/gcoap.h"
#include "net/utils.h"
#include "od.h"

static ssize_t _gps_handler(coap_pkt_t *pdu, uint8_t *buf, size_t len, coap_request_ctx_t *ctx);
static void _resp_handler(const gcoap_request_memo_t *memo, coap_pkt_t* pdu, const sock_udp_ep_t *remote);

static const coap_resource_t _resources[] = {
    { "/gps", COAP_GET, _gps_handler, NULL }
};

/* a gcoap listener is a collection of resources. Additionally we can specify
 * custom functions to:
 *      - list our resources on the /.well-known/core
 *      - how our resources are matched on an incoming request (simple string
 *        comparison is the default)
 */
static gcoap_listener_t _listener = {
    _resources,
    ARRAY_SIZE(_resources),
    GCOAP_SOCKET_TYPE_UDP,
    NULL,
    NULL,
    NULL
};

void server_init(void) {
    gcoap_register_listener(&_listener);
}

static void _resp_handler(const gcoap_request_memo_t *memo, coap_pkt_t* pdu, const sock_udp_ep_t *remote) {
    (void)remote;       /* not interested in the source currently */

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
            /* Expecting diagnostic payload in failure cases */
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

static bool _parse_endpoint(sock_udp_ep_t *remote,
                            const char *addr_str, const char *port_str) {
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

static size_t _send(uint8_t *buf, size_t len, char *addr_str, char *port_str) {
    size_t bytes_sent;
    sock_udp_ep_t remote;

    if (!_parse_endpoint(&remote, addr_str, port_str)) {
        return 0;
    }

    bytes_sent = gcoap_req_send(buf, len, &remote, _resp_handler, NULL);
    if (bytes_sent > 0) {
        //req_count++;
    }
    return bytes_sent;
}

size_t send_req(char *addr, char *port, char *path, char *data, unsigned method) {
    uint8_t buf[CONFIG_GCOAP_PDU_BUF_SIZE];
    coap_pkt_t pdu;
    size_t len;

    size_t data_len = strlen(data);

    if(data != NULL) {
        /* initialize the CoAP request */
        gcoap_req_init(&pdu, buf, CONFIG_GCOAP_PDU_BUF_SIZE, method, path);

        /* send a confirmable message */
        coap_hdr_set_type(pdu.hdr, COAP_TYPE_CON);

        /* specify the plain text format and copy the payload */
        // wir senden nur mit payload -> überprüfung überflüssig/früher möglich
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
        if (!_send(buf, len, addr, port)) {
            puts("gcoap_cli: msg send failed");
            return -1;
        }
    } else {
        puts("No payload");
        return -1;
    }
    return 0;
}

#define TEST_MSG "hello gps"

static ssize_t _gps_handler(coap_pkt_t *pdu, uint8_t *buf, size_t len, coap_request_ctx_t *ctx) {
    (void) ctx; /* argument not used */

    /* initialize a new coap response */
    gcoap_resp_init(pdu, buf, len, COAP_CODE_CONTENT);

    /* first we set all the options */
    /* set the format option to "plain text" */
    coap_opt_add_format(pdu, COAP_FORMAT_TEXT);

    /* finish the options sections */
    /* it is important to keep track of the amount of used bytes (resp_len) */
    size_t resp_len = coap_opt_finish(pdu, COAP_OPT_FINISH_PAYLOAD);

    /* write the RIOT board name in the response buffer */
    if (pdu->payload_len >= strlen(TEST_MSG)) {
        memcpy(pdu->payload, TEST_MSG, strlen(TEST_MSG));
        return resp_len + strlen(TEST_MSG);
    } else {
        /* in this case we use a simple convenience function to create the
         * response, it only allows to set a payload and a response code. */
        puts("gcoap_cli: msg buffer too small");
        return gcoap_response(pdu, buf, len, COAP_CODE_INTERNAL_SERVER_ERROR);
    }
}

void send_to_concentrator(const char* msg) {
    //send_req("fe80::fcb2:9130:a6fa:74b3", "5683", coap_path, sensor_data, COAP_POST);
    printf("send msg to %s: %s\n", CONCENTRATOR_IP, msg);
}
