#include <stdio.h>

#include "lis2dh12.h"
#include "lis2dh12_params.h"
#include "lis2dh12_registers.h"
#include "periph/gpio.h"
#include "ztimer.h"
#include "coap.h"

/* ------------------------------------------------ */
/*          Start security initialization           */
/* ------------------------------------------------ */
#include "provisioning_helper.h"
//#include "sec_link_layer.h"
//static ieee802154_sec_context_t link_layer_sec_ctx;
/* ------------------------------------------------ */
/*           End security initialization            */
/* ------------------------------------------------ */

#define ACCEL_THRESHOLD     5000   // Acceleration threshold in mg
#define THRESHOLD_TIME_US   0   // Threshold time until interrupt occurs

/*
 * The program is only configured to react to interrupts, when the ACCEL_THRESHOLD value is exceeded. 
 * The acceleration values are not read because the config of the FIFO is too slow and the driver has some missing functionality.
 */

void initDevice(lis2dh12_t *dev, lis2dh12_params_t *params);
void configureThresholdEvent(lis2dh12_t *dev);

void initDevice(lis2dh12_t *dev, lis2dh12_params_t *params){
    // Set params
    params->addr = 0x18;
    params->rate = LIS2DH12_RATE_1HZ; // Lowest possible rate to save energy
    params->resolution = LIS2DH12_POWER_LOW;    // 8 bit resolution
    params->scale = LIS2DH12_SCALE_16G;  // Acceleration Range, +-16g is highest possible
    params->int1_pin = GPIO_PIN(1, 8);  // Pin D5 on board
    // params->int2_pin = GPIO_PIN(0, 7);   // Optional second interrupt pin

    // Initialize sensor
    while(lis2dh12_init(dev, params) != LIS2DH12_OK){
        puts("lis2dh12 init failed. Trying again in 1 second.");
        ztimer_sleep(ZTIMER_SEC, 1);
    }
    puts("lis2dh12 initialized.");

    // Bypass FIFO
    lis2dh12_fifo_t fifo_cfg = {
        .FIFO_mode = LIS2DH12_FIFO_MODE_BYPASS,
        .FIFO_watermark = 10,
        .FIFO_set_INT2 = false,
    };

    lis2dh12_set_fifo(dev, &fifo_cfg);

    configureThresholdEvent(dev);
}

void configureThresholdEvent(lis2dh12_t *dev){

    // Configure threshold above which interrupt should occur
    uint32_t mg = ACCEL_THRESHOLD;
    uint32_t us = THRESHOLD_TIME_US;
    uint8_t axis = LIS2DH12_INT_CFG_XHIE
                 | LIS2DH12_INT_CFG_YHIE
                 | LIS2DH12_INT_CFG_ZHIE;
    uint8_t event = LIS2DH12_EVENT_1;
    
    lis2dh12_cfg_threshold_event(dev, mg, us, axis, event, LIS2DH12_INT1);
}

int main(void)
{
    /* ------------------------------------------------ */
    /*          Start security initialization           */
    /* ------------------------------------------------ */
    provisioning_helper_init();
    //sec_link_layer_init(&link_layer_sec_ctx);
    /* ------------------------------------------------ */
    /*           End security initialization            */
    /* ------------------------------------------------ */

    i2c_t dev = I2C_DEV(0);
    lis2dh12_t sensorDev; // Device descriptor
    lis2dh12_params_t sensorParams;
    sensorParams.i2c = dev;
    char answerStream[] = "Impact over 5G";

    // Initialize sensor
    initDevice(&sensorDev, &sensorParams);

    coap_path = "/acceleration";
    discover_concentrator();

    while(1){
        // Wait for interrupt, function uses mutex
        if(lis2dh12_wait_event(&sensorDev, LIS2DH12_INT1, false) < 0){
            printf("Interrupt error\n");
        }
        send_to_concentrator(answerStream);
        puts("Interrupt occured.");
    }  
}
