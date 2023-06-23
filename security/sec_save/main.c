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
    
    sec_save(); // #TODO Remove, for testing only

    return 0;
}