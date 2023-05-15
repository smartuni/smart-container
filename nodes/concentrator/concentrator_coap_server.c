#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fmt.h"
#include "net/gcoap.h"
#include "net/utils.h"
#include "od.h"

#include "gcoap_example.h"

#include "periph/gpio.h"
#include "board.h"

static ssize_t _temperature_handler(coap_pkt_t* pdu, uint8_t *buf, size_t len, coap_request_ctx_t *ctx);
static ssize_t _humidity_handler(coap_pkt_t* pdu, uint8_t *buf, size_t len, coap_request_ctx_t *ctx);
static ssize_t _waterleak_handler(coap_pkt_t* pdu, uint8_t *buf, size_t len, coap_request_ctx_t *ctx);
static ssize_t _door_handler(coap_pkt_t* pdu, uint8_t *buf, size_t len, coap_request_ctx_t *ctx);
static ssize_t _gps_handler(coap_pkt_t* pdu, uint8_t *buf, size_t len, coap_request_ctx_t *ctx);
static ssize_t _acceleration_handler(coap_pkt_t* pdu, uint8_t *buf, size_t len, coap_request_ctx_t *ctx);

/* CoAP resources. Must be sorted by path (ASCII order). */
static const coap_resource_t _resources[] = {
    { "/acceleration", COAP_POST, _acceleration_handler, NULL },
    { "/door", COAP_POST, _door_handler, NULL },
    { "/gps", COAP_POST, _gps_handler, NULL },
    { "/humidity", COAP_POST, _humidity_handler, NULL },
    { "/temperature", COAP_POST, _temperature_handler, NULL },
    { "/waterleak", COAP_POST, _waterleak_handler, NULL },
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

void server_init(void)
{
    gcoap_register_listener(&_listener);
}

static ssize_t _temperature_handler(coap_pkt_t *pdu, uint8_t *buf, size_t len, coap_request_ctx_t *ctx)
{
    (void)ctx;
    (void)buf;
    (void)len;

    if (pdu->payload_len > 0) {
        printf("Temperature: %s\n", (char *)pdu->payload);
    }

    return gcoap_response(pdu, buf, len, COAP_CODE_CREATED);
}

static ssize_t _humidity_handler(coap_pkt_t *pdu, uint8_t *buf, size_t len, coap_request_ctx_t *ctx)
{
    (void)ctx;
    (void)buf;
    (void)len;

    if (pdu->payload_len > 0) {
        printf("Humidity: %s\n", (char *)pdu->payload);
    }

    return gcoap_response(pdu, buf, len, COAP_CODE_CREATED);
}

static ssize_t _waterleak_handler(coap_pkt_t *pdu, uint8_t *buf, size_t len, coap_request_ctx_t *ctx)
{
    (void)ctx;
    (void)buf;
    (void)len;

    if (pdu->payload_len > 0) {
        printf("Waterleak: %s\n", (char *)pdu->payload);
    }

    return gcoap_response(pdu, buf, len, COAP_CODE_CREATED);
}

static ssize_t _door_handler(coap_pkt_t *pdu, uint8_t *buf, size_t len, coap_request_ctx_t *ctx)
{
    (void)ctx;
    (void)buf;
    (void)len;

    if (pdu->payload_len > 0) {
        printf("Door: %s\n", (char *)pdu->payload);
    }

    return gcoap_response(pdu, buf, len, COAP_CODE_CREATED);
}

static ssize_t _gps_handler(coap_pkt_t *pdu, uint8_t *buf, size_t len, coap_request_ctx_t *ctx)
{
    (void)ctx;
    (void)buf;
    (void)len;

    if (pdu->payload_len > 0) {
        printf("GPS: %s\n", (char *)pdu->payload);
    }

    return gcoap_response(pdu, buf, len, COAP_CODE_CREATED);
}

static ssize_t _acceleration_handler(coap_pkt_t *pdu, uint8_t *buf, size_t len, coap_request_ctx_t *ctx)
{
    (void)ctx;
    (void)buf;
    (void)len;

    if (pdu->payload_len > 0) {
        printf("Acceleration: %s\n", (char *)pdu->payload);
    }

    return gcoap_response(pdu, buf, len, COAP_CODE_CREATED);
}