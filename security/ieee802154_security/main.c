/*
 * Copyright (C) 2020 ML!PA Consulting GmbH
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     tests
 * @{
 *
 * @file
 * @brief       Test application for network device drivers
 *
 * @author      Benjamin Valentin <benjamin.valentin@ml-pa.com>
 * @}
 */

#include "thread.h"
#include "shell.h"
#include "crypto/ciphers.h"
#include "net/ieee802154_security.h"
#include "net/gnrc/pktdump.h"
#include "net/gnrc/netif.h"
#include "net/gnrc.h"

#include "log.h"
#include "od.h"

int main(void)
{
    getchar();

    ieee802154_sec_context_t link_layer_sec_ctx;
    
    uint8_t key[16] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };

    ieee802154_sec_init(&link_layer_sec_ctx);

    cipher_init(&link_layer_sec_ctx.cipher, CIPHER_AES, key, IEEE802154_SEC_KEY_LENGTH);
    
    printf("security_level = %d\n", link_layer_sec_ctx.security_level);
    printf("key_id_mode = %d\n", link_layer_sec_ctx.key_id_mode);
    printf("key_index = %d\n", link_layer_sec_ctx.key_index);
    printf("key_source: \n");
    od_hex_dump(link_layer_sec_ctx.key_source, IEEE802154_LONG_ADDRESS_LEN, OD_WIDTH_DEFAULT);
    printf("frame_counter = %ld\n",link_layer_sec_ctx.frame_counter);

    ///////////////////////////
    /* enable pktdump output */
    gnrc_netreg_entry_t dump = GNRC_NETREG_ENTRY_INIT_PID(GNRC_NETREG_DEMUX_CTX_ALL,
                                                          gnrc_pktdump_pid);

    gnrc_netreg_register(GNRC_NETTYPE_UNDEF, &dump);

    /* start the shell */
    char line_buf[SHELL_DEFAULT_BUFSIZE];

    shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}