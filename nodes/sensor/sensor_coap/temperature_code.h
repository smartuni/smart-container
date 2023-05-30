// temperature sensor specific code 

// Not needed when using saul
//#include "board.h"
//#include "bmx280.h"
#include "saul_reg.h"
#include "ztimer.h"
#include "phydat.h"
#include "stddef.h"
#include "fmt.h"
#include "math.h"

// define variables
char *coap_path = "/temperature";

//define function

 size_t read_sensor(char *sensor_value_string, size_t length){

    size_t actual_length;
    phydat_t temperature;
    saul_reg_t *temp_sensor = saul_reg_find_type(SAUL_SENSE_TEMP);

    puts("Initialize bme280 temperature sensor");

    if(!temp_sensor){
        puts("No temperature sensor present");
        return 1;
    }
    else{
        printf("Found temperature device: %s\n", temp_sensor->name);
    }

    int dimensions = saul_reg_read(temp_sensor, &temperature);
    if (dimensions < 1) {
        puts("Error reading temp value from device");
        return 1;
    }
    phydat_dump(&temperature, dimensions);
    
    actual_length = fmt_float(sensor_value_string, (float) temperature.val[0] * pow(10, temperature.scale), 2);
    if (actual_length < length) {
        sensor_value_string[actual_length] = '\0';
    } else {
        puts("Error writting data");
        return 1;
    }

    return 0;
}