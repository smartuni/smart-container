#include "sec_save.h"

/*************************************************************
 * Encryption functions
 ************************************************************/
static int encrypt_buf(uint8_t *cipher_text, uint8_t *key, const uint8_t *buf, size_t buf_len)
{
    // Add edge case for buf_len and padding
    cipher_t cipher;

    if (cipher_init(&cipher, CIPHER_AES, key, AES_KEY_SIZE) < 0)
    {
        return -1;
    }

    unsigned int i;
    for (i = 0; i < buf_len / AES_BLOCK_SIZE; ++i)
    {
        if (cipher_encrypt(&cipher, buf + i * AES_BLOCK_SIZE, cipher_text + i * AES_BLOCK_SIZE) < 0)
        {
            return -1;
        }
    }

    return 0;
}

void sec_save(const char *filename, uint8_t *buf_enc, const uint8_t *buf, size_t buf_len)
{
    uint8_t sec_save_aes_key[AES_KEY_SIZE];
    provisioning_helper_get_sec_save_aes_key(sec_save_aes_key);

    LOG_INFO("Plaintext is: \n");
    od_hex_dump(buf, buf_len, OD_WIDTH_DEFAULT);

    encrypt_buf(buf_enc, sec_save_aes_key, buf, buf_len);
    LOG_INFO("Ciphertext is: \n");
    od_hex_dump(buf_enc, buf_len, OD_WIDTH_DEFAULT);
    
    sdcard_fs_write(filename, (char *) buf_enc, buf_len);

    return;
}
