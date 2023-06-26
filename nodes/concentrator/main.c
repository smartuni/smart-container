/*
 * Copyright (c) 2015-2016 Ken Bannister. All rights reserved.
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include <stdio.h>
#include "msg.h"

#include "net/gcoap.h"
#include "shell.h"
#include "event/periodic_callback.h"
#include "event/thread.h"
#include "ztimer.h"
#include "periph/gpio.h"

/* ------------------------------------------------ */
/*          Start security initialization           */
/* ------------------------------------------------ */
#include "provisioning_helper.h"
#include "sdcard_fs.h"
//#include "link_layer_security.h"
#include "sec_save.h"

//static ieee802154_sec_context_t link_layer_sec_ctx;
/* ------------------------------------------------ */
/*           End security initialization            */
/* ------------------------------------------------ */

#include "gcoap_example.h"
#include "concentrator_lorawan.h"
#include "cycling_buffer.h"

#define MAIN_QUEUE_SIZE (4)
static msg_t _main_msg_queue[MAIN_QUEUE_SIZE];

#define BUFFER_FLUSH_INTERVAL (10U)
static event_periodic_callback_t buffer_flush_event;

static const shell_command_t shell_commands[] = {
    { "coap", "CoAP example", gcoap_cli_cmd },
    { NULL, NULL, NULL }
};

void buffer_flush_cb(void* args)
{
    (void)args;
    printf("callback");
    send_data_list(getCyclingBuffer());
    clearCyclingBuffer();
}

void event_init(void)
{
    /* initialize periodic callback */
    event_periodic_callback_init(&buffer_flush_event, ZTIMER_SEC, EVENT_PRIO_MEDIUM,
                                 buffer_flush_cb, NULL);
    /* start periodic callback */
    event_periodic_callback_start(&buffer_flush_event, BUFFER_FLUSH_INTERVAL);
}

int main(void)
{
    /* ------------------------------------------------ */
    /*          Start security initialization           */
    /* ------------------------------------------------ */
    sdcard_fs_init();
    provisioning_helper_init();
    //link_layer_sec_init(&link_layer_sec_ctx);
    /* ------------------------------------------------ */
    /*           End security initialization            */
    /* ------------------------------------------------ */

    /* for the thread running the shell */
    msg_init_queue(_main_msg_queue, MAIN_QUEUE_SIZE);

    /* init cycling buffer for in ram storage of sensor data*/
    initCyclingBuffer();

    /* init lorawan */
    puts("LoRaWAN Sensor application"); /* Setup button callback */
    if (gpio_init_int(BTN0_PIN, BTN0_MODE, GPIO_FALLING, button_callback, NULL) < 0)
    {
        puts("[FAILED] init BTN0!");
        return 1;
    } /* Try to get a LoRaWAN interface */
    gnrc_netif_t* lorawan_netif = NULL;
    if (!(lorawan_netif = get_lorawan_netif()))
    {
        puts("Couldn't find a LoRaWAN interface");
        return 1;
    }
    activate(lorawan_netif);

    server_init();
    
    event_init();
    
    
    /* start shell */
    puts("All up, running the shell now");
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    /* should never be reached */
    return 0;
}

