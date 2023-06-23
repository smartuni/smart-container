#include <stdio.h>

#include "provisioning_helper.h"
#include "sdcard_fs.h"
#include "sec_save.h"

int main(void)
{
    /* Security initialization */
    getchar(); // Needed for nrf52840

    /* ------------------------------------------------ */
    /*          Start security initialization           */
    /* ------------------------------------------------ */
    sdcard_fs_init();
    provisioning_helper_init();
    /* ------------------------------------------------ */
    /*           End security initialization            */
    /* ------------------------------------------------ */

    /* ------------------------------------------------ */
    /*              Start security testing              */
    /* ------------------------------------------------ */
    char *filename = "TEST2.TXT";

    // size_t num_blocks = 8;
    uint8_t plain_text[AES_BLOCK_SIZE * 8];
    uint8_t cipher_text[sizeof(plain_text)];
    random_bytes(plain_text, sizeof(plain_text));

    sec_save(filename, cipher_text, plain_text, sizeof(plain_text));
    /* ------------------------------------------------ */
    /*                End security testing              */
    /* ------------------------------------------------ */

    return 0;
}