#include <stdio.h>

#include "provisioning_helper.h"
#include "sdcard_fs.h"
#include "sec_save.h"

int main(void)
{
    getchar(); // Needed for nrf52840

    /* ------------------------------------------------ */
    /*          Start security initialization           */
    /* ------------------------------------------------ */
    sdcard_fs_init();
    provisioning_helper_init();
    /* ------------------------------------------------ */
    /*          End security initialization           */
    /* ------------------------------------------------ */

    /* ------------------------------------------------ */
    /*              Start security testing              */
    /* ------------------------------------------------ */
    // #ifdef PROVISIONING_ENABLE_DEV 
    // #TODO Remove, for testing only
    const char *filename = "TEST.TXT"; 
    
    size_t num_blocks = 8;
    uint8_t buf[128 * num_blocks];
    uint8_t buf_out[128 * num_blocks];
    random_init(0); random_bytes(buf, sizeof(buf));
    size_t buf_len = sizeof(buf);

    LOG_INFO("Plaintext is: \n");
    od_hex_dump(buf, buf_len, OD_WIDTH_DEFAULT);

    LOG_INFO("Starting sec_save.\n");
    sec_save(filename, buf_out, buf, buf_len);

    // #endif
    /* ------------------------------------------------ */
    /*          End security initialization           */
    /* ------------------------------------------------ */
    
    return 0;
}
