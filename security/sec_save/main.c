#include <stdio.h>

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
#include "sdcard_fs.h"
#include "link_layer_security.h"
#include "sec_save.h"

static ieee802154_sec_context_t link_layer_sec_ctx;

int main(void)
{
    /* Security initialization */
    // getchar(); // Needed for nrf52840

    /* ------------------------------------------------ */
    /*          Start security initialization           */
    /* ------------------------------------------------ */
    sdcard_fs_init();
    provisioning_helper_init();
    link_layer_sec_init(&link_layer_sec_ctx);
    /* ------------------------------------------------ */
    /*           End security initialization            */
    /* ------------------------------------------------ */

    /* ------------------------------------------------ */
    /*              Start security testing              */
    /* ------------------------------------------------ */
    char *filename = "TEST2.TXT";

    // size_t num_blocks = 8;
    uint8_t plain_text[AES_BLOCK_SIZE * 8];
    random_bytes(plain_text, sizeof(plain_text));

    sec_save(filename, plain_text, sizeof(plain_text));

    ///////////////////////////
    /* enable pktdump output */
    gnrc_netreg_entry_t dump = GNRC_NETREG_ENTRY_INIT_PID(GNRC_NETREG_DEMUX_CTX_ALL,
                                                          gnrc_pktdump_pid);

    gnrc_netreg_register(GNRC_NETTYPE_UNDEF, &dump);

    /* start the shell */
    char line_buf[SHELL_DEFAULT_BUFSIZE];

    shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);
    /* ------------------------------------------------ */
    /*                End security testing              */
    /* ------------------------------------------------ */

    return 0;
}