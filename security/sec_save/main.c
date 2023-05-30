/*
 * Copyright (C) 2014 Freie Universität Berlin
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
 * @brief       Hello World application
 *
 * @author      Kaspar Schleiser <kaspar@schleiser.de>
 * @author      Ludwig Knüpfer <ludwig.knuepfer@fu-berlin.de>
 *
 * @}
 */

#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "periph/rtc.h"
#include "od.h"
#include "ztimer.h"
#include "crypto/ciphers.h"
#include "crypto/aes.h"

#include "shell.h"
#include "sdcard_spi.h"
#include "sdcard_spi_internal.h"
#include "sdcard_spi_params.h"
#include "fmt.h"
#include "container.h"
#include <inttypes.h>
#include <stdlib.h>

#include "config.h"
#include "sdcard.h"
#include "sec_save.h"

int main(void)
{
    fprintf(PRINT_FILE, "You are running RIOT on a(n) %s board.\n", RIOT_BOARD);
    fprintf(PRINT_FILE, "This board features a(n) %s MCU.\n", RIOT_MCU);

    cipher_t cipher;
    ztimer_init(); // Initialize timer
    init_sec_save();

    while (1)
    {
        uint8_t key[AES_KEY_SIZE_128] = {0},
                plain_text[AES_BLOCK_SIZE] = {0},
                cipher_text[AES_BLOCK_SIZE] = {0};

        if (cipher_init(&cipher, CIPHER_AES, key, AES_KEY_SIZE_128) < 0)
            fprintf(PRINT_FILE, "Cipher init failed!\n");

        if (cipher_encrypt(&cipher, plain_text, cipher_text) < 0)
            fprintf(PRINT_FILE, "Cipher encryption failed!\n");
        else
        {
            od_hex_dump(key, AES_BLOCK_SIZE, 0);
            od_hex_dump(plain_text, AES_BLOCK_SIZE, 0);
            od_hex_dump(cipher_text, AES_BLOCK_SIZE, 0);
        }

        ztimer_now_t time = ztimer_now(ZTIMER_MSEC);
        od_hex_dump((uint8_t *)&time, sizeof(time), 0);

        od_hex_dump((uint8_t *)&time_now, sizeof(time_now), 0);

        ztimer_now_t last_wakeup = ztimer_now(ZTIMER_MSEC);
        /* wait for 500 ms */
        ztimer_periodic_wakeup(ZTIMER_MSEC, &last_wakeup, 500);
    }

    return 0;
}
