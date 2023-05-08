#include "stdint.h"

#include "crypto/ciphers.h"
#include "phydat.h"

#include "sec_save_config.h"
#include "sec_save_sdcard.h"
#include "sec_save.h"

#define SERIALIZED_PHYDAT_SIZE 512
#define SERIALIZED_PHYDAT_DIM 1
#define AES_KEY_SIZE 128
#define AES_BLOCK_SIZE 128

size_t serialize_phydat(uint8_t *serialized_phydat, const phydat_t *phydat)
{
    size_t serialized_phydat_size = phydat_to_json(phydat, SERIALIZED_PHYDAT_DIM, serialize_phydat);

    if (serialized_phydat_size > SERIALIZED_PHYDAT_SIZE)
    {
        return -1;
    }

    return serialized_phydat_size;
}

int encrypt_buf(uint8_t *key, uint8_t *plain_text, uint8_t *cipher_text)
{
    cipher_t cipher;

    if (cipher_init(&cipher, CIPHER_AES, key, AES_KEY_SIZE) < 0)
    {
        return -1;
    }

    if (cipher_encrypt(&cipher, plain_text, cipher_text) < 0)
    {
        return -1;
    }

    return 1;
}

int sec_save(phydat_t *phydat)
{
    size_t serialized_phydat_size = 0;
    uint8_t serialized_phydat[SERIALIZED_PHYDAT_SIZE] = {0};

    // Serialize data
    serialized_phydat_size = serialize_phydat(&serialized_phydat, phydat);
    if (serialized_phydat_size < 0)
    {
        return -1;
    }

    // Encrypt serialized data buffer
    uint8_t key[AES_KEY_SIZE] = {0};
    uint8_t plain_text[AES_BLOCK_SIZE] = {0};
    uint8_t cipher_text[AES_BLOCK_SIZE] = {0};
    if (encrypt_buf(&key, &plain_text, &cipher_text) < 0)
    {
        return -1;
    }

    // Persist data in SD card

    init_sdcard(void); // Initialize SD Card

    sd_rw_response_t state;
    int chunks_written = sdcard_spi_write_blocks(card, bladdr, write_buffer, SD_HC_BLOCK_SIZE, 1, &state);

    if (state != SD_RW_OK)
    {
        printf("write error %d (wrote %d/%d blocks)\n", state, chunks_written, 1);
        return -1;
    }
}