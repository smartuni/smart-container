#include <stdio.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    uint16_t deviceID;
    uint8_t secSave_AES128[16]; // Only for concentrator node
    uint8_t TLS_PSK_AES128[16];
    uint8_t ECC256[48]; // For later use
    uint8_t certificates[2048]; // For later use
    uint8_t LoRaWANData[128];
    uint8_t TP_IP_Read[16]; // CPU ID & MAC encryption key (TP_IP_Read)
} EEPROMStruct;

int main() {
    EEPROMStruct eepromStruct;

    // Fill struct with appropriate data
    eepromStruct.deviceID = YOUR_DEVICE_ID; // replace this with the actual device ID

    // Include the auto-generated key file
    #include "psk_key.c"
    memcpy(eepromStruct.TLS_PSK_AES128, psk_key, sizeof(psk_key));

    // Rest of your code here, using the `eepromStruct` as needed

    return 0;
}
