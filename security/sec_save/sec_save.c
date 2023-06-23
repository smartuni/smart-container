#include "sec_save.h"

/*************************************************************
 * Encryption functions
 ************************************************************/
static int encrypt_buf(uint8_t *cipher_text, uint8_t *key, uint8_t *buf, size_t buf_len)
{
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

void sec_save(void)
{
    uint8_t sec_save_aes_key[AES_KEY_SIZE];
    provisioning_helper_get_sec_save_aes_key(sec_save_aes_key);
    
    size_t num_blocks = 8;
    uint8_t plain_text[AES_BLOCK_SIZE * num_blocks];
    uint8_t cipher_text[sizeof(plain_text)];
    random_bytes(plain_text, sizeof(plain_text));

    plain_text[sizeof(plain_text) - 1] = 0x00; // Null terminating string
    LOG_INFO("Plaintext is: \n");
    // od_hex_dump(plain_text, sizeof(plain_text), OD_WIDTH_DEFAULT);

    encrypt_buf(cipher_text, sec_save_aes_key, plain_text, sizeof(plain_text));
    LOG_INFO("Ciphertext is: \n");
    // od_hex_dump(cipher_text, sizeof(cipher_text), OD_WIDTH_DEFAULT);
    
    sdcard_fs_write((char *) cipher_text, sizeof(cipher_text));

    return;
}
