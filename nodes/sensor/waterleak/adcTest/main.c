#include <stdio.h>

#include "board.h"
#include "saul_reg.h"

int main(void) {

    printf("Hello World.\n");

    saul_reg_t *adc = saul_reg_find_type(SAUL_SENSE_ANALOG);
    if(!adc) {
        puts("No adc present");
        return 1;
    } else {
        printf("Found adc: %s\n", adc->name);
    }

    return 0;

}