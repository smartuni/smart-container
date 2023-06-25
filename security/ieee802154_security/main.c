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

#include "provisioning_helper.h"
#include "link_layer_security.h"

static ieee802154_sec_context_t link_layer_sec_ctx;

int main(void)
{
    getchar(); // Needed for nrf52840

    /* ------------------------------------------------ */
    /*          Start security initialization           */
    /* ------------------------------------------------ */
    // sdcard_fs_init();
    provisioning_helper_init();
    link_layer_sec_init(&link_layer_sec_ctx);
    /* ------------------------------------------------ */
    /*           End security initialization            */
    /* ------------------------------------------------ */
    
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