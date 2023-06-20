/*
 * Copyright (c) 2015-2016 Ken Bannister. All rights reserved.
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     examples
 * @{
 *
 * @file
 * @brief       gcoap example
 *
 * @author      Ken Bannister <kb2ma@runbox.com>
 *
 * @}
 */

#include <stdio.h>
#include "msg.h"
#include "od.h"
#include "net/gcoap.h"
#include "shell.h"

#define CREDMAN_CONFIG_CONCENTRATOR 0
#include "credman_helper.h"


#include "gcoap_example.h"

#define MAIN_QUEUE_SIZE (4)
static msg_t _main_msg_queue[MAIN_QUEUE_SIZE];

static const shell_command_t shell_commands[] = {
    { "coap", "CoAP example", gcoap_cli_cmd },
    { NULL, NULL, NULL }
};

int main(void)
{
    getchar(); // Wait till key is pressed, otherwise term on nrf52840 doesn't work

    /* Checking provisioned key */
    uint8_t psk_id[CREDMAN_FLASH_LEN_DEVICE_ID];
    uint8_t psk_key[CREDMAN_FLASH_LEN_DTLS_PSK_AES_KEY];
    read_psk(psk_id, psk_key);

    od_hex_dump(psk_id, CREDMAN_FLASH_LEN_DEVICE_ID, OD_WIDTH_DEFAULT);
    od_hex_dump(psk_key, CREDMAN_FLASH_LEN_DTLS_PSK_AES_KEY, OD_WIDTH_DEFAULT);

    /* for the thread running the shell */
    msg_init_queue(_main_msg_queue, MAIN_QUEUE_SIZE);
    server_init();
    puts("gcoap example app");

    /* start shell */
    puts("All up, running the shell now");
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    /* should never be reached */
    return 0;
}
