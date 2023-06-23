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
#include "log.h"
#include "msg.h"
#include "od.h"
#include "shell.h"
#include "mtd.h"
#include "random.h"
#include "mtd_flashpage.h"

#define CREDMAN_CONFIG_CONCENTRATOR 0
#include "credman_helper.h"

// #include "net/gcoap.h"
// #include "gcoap_example.h"

// #define MAIN_QUEUE_SIZE (4)
// static msg_t _main_msg_queue[MAIN_QUEUE_SIZE];

// static const shell_command_t shell_commands[] = {
//     { "coap", "CoAP example", gcoap_cli_cmd },
//     { NULL, NULL, NULL }
// };

static mtd_flashpage_t _mtd_dev = MTD_FLASHPAGE_INIT_VAL(8); 
static mtd_dev_t *mtd_dev = &_mtd_dev.base;

int main(void)
{
    random_init(0);
    getchar(); // Wait till key is pressed, otherwise term on nrf52840 doesn't work
    
    init_provisioning(mtd_dev);

    /* Checking provisioned key */
    uint8_t psk_id[CREDMAN_FLASH_LEN_DEVICE_ID];
    uint8_t psk_key[CREDMAN_FLASH_LEN_DTLS_PSK_AES_KEY];
    read_psk(mtd_dev, psk_id, psk_key);

    LOG_INFO("Retrieved the following DEVICE_ID from MTD:\n");
    od_hex_dump(psk_id, CREDMAN_FLASH_LEN_DEVICE_ID, OD_WIDTH_DEFAULT);
    LOG_INFO("Retrieved the following DTLS_PSK_AES_KEY from MTD:\n");
    od_hex_dump(psk_key, CREDMAN_FLASH_LEN_DTLS_PSK_AES_KEY, OD_WIDTH_DEFAULT);

    /* for the thread running the shell */
    // msg_init_queue(_main_msg_queue, MAIN_QUEUE_SIZE);
    // server_init();
    // puts("gcoap example app");

    // /* start shell */
    // puts("All up, running the shell now");
    // char line_buf[SHELL_DEFAULT_BUFSIZE];
    // shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    /* should never be reached */
    return 0;
}
