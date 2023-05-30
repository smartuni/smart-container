#include <stdio.h>
#include <math.h>

#include "fmt.h"
#include "lis2dh12.h"
#include "lis2dh12_params.h"
#include "lis2dh12_registers.h"
#include "periph/gpio.h"

#define ACCEL_THRESHOLD     7000   // Acceleration threshold in mg
#define THRESHOLD_TIME_US   1000   // Threshold time until interrupt occurs

#define NUM_FIFO_VALUES 32

void initDevice(lis2dh12_t *dev, lis2dh12_params_t *params){
    // Set params
    params->addr = 0x18;
    params->rate = LIS2DH12_RATE_50HZ; // Rate 5376 Hz in Low power mode, else 1344
    params->resolution = LIS2DH12_POWER_LOW;    // 8 bit resolution
    params->scale = LIS2DH12_SCALE_8G;  // May be changed to 16g later
    params->int1_pin = GPIO_PIN(1, 8);  // Pin D5 on board
    // params->int2_pin = GPIO_PIN(0, 7);   // Optional second interrupt pin


    if(lis2dh12_init(dev, params) == LIS2DH12_OK) {
        puts("lis2dh12 initialized");
    }
    else {
        puts("lis2dh12 init failed");
    }

    // Set Fifo mode to continous buffered stream (32 values in ringbuffer without overflow)
    lis2dh12_fifo_t fifo_cfg = {
        .FIFO_mode = LIS2DH12_FIFO_MODE_STREAM,
    };

    lis2dh12_set_fifo(dev, &fifo_cfg);
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

int main(void){
    i2c_t dev = I2C_DEV(0);
    lis2dh12_t sensorDev; // Device descriptor
    lis2dh12_params_t sensorParams;
    sensorParams.i2c = dev;

    uint8_t num = NUM_FIFO_VALUES;
    lis2dh12_fifo_data_t data[NUM_FIFO_VALUES];
    long long maxAcceleration = 0;
    long long tempAcceleration = 0;
    int maxIndex = 0;

    // Initialize sensor
    initDevice(&sensorDev, &sensorParams);

    configureThresholdEvent(&sensorDev);

    while(1){

        // Wait for interrupt, function uses mutex
        if(lis2dh12_wait_event(&sensorDev, LIS2DH12_INT1, false) < 0){
            printf("Interrupt error\n");
        }

        // Read values of fifo, should be 32. 
        num = lis2dh12_read_fifo_data(&sensorDev, data, num);

        // search for value where acceleration is the highest
        maxAcceleration = 0;
        for (unsigned i = 0; i < num; i++){
            for (unsigned j = 0; j < 3; j++){
                tempAcceleration = data[i].data[j] * data[i].data[j];
                if(tempAcceleration > maxAcceleration){
                    maxIndex = i;
                    maxAcceleration = tempAcceleration;
                }  
            }
            //tempAcceleration = sqrt(((float)data[i].axis.x)*0.001 * ((float)data[i].axis.x)*0.001 +
            //                        ((float)data[i].axis.y)*0.001 * ((float)data[i].axis.y)*0.001 +
            //                       ((float)data[i].axis.z)*0.001 * ((float)data[i].axis.z)*0.001);
        }
        //char str_out[10];
        char singleString[3][10];
        //size_t len = fmt_float(str_out, maxAcceleration, 3);
        //str_out[len] = '\0';
        //printf("Max Acceleration: %s g \n", str_out);

        // Convert values to string and print them
        size_t len = fmt_float(singleString[0], ((float)data[maxIndex].axis.x)*0.001, 3);
        singleString[0][len] = '\0';
        len = fmt_float(singleString[1], ((float)data[maxIndex].axis.y)*0.001, 3);
        singleString[1][len] = '\0';
        len = fmt_float(singleString[2], ((float)data[maxIndex].axis.z)*0.001, 3);
        singleString[2][len] = '\0';
        printf("Single values x: %s, y: %s, z: %s\n", singleString[0], singleString[1], singleString[2]);
    }  
}