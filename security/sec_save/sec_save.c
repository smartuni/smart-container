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

void sec_save(const char *filename, uint8_t *buf_out, uint8_t *buf, const size_t buf_len)
{
    LOG_INFO("Inside sec_save.\n");

    uint8_t sec_save_aes_key[AES_KEY_SIZE];
    provisioning_helper_get_sec_save_aes_key(sec_save_aes_key);

    LOG_INFO("Plaintext is: \n");
    od_hex_dump(buf, buf_len, OD_WIDTH_DEFAULT);

    // // Dynamically allocate memory for cipher_text
    // uint8_t *cipher_text = (uint8_t *)malloc(buf_len * sizeof(uint8_t)); // TODO Handle padding
    // if (cipher_text == NULL) {
    //     LOG_ERROR("Failed to allocate memory for cipher_text\n");
    //     return;
    // }

    LOG_INFO("Started buffer encryption.\n");
    getchar(); // #TODO Remove, for debugging

    encrypt_buf(buf_out, sec_save_aes_key, buf, buf_len);
    LOG_INFO("Ciphertext is: \n");
    od_hex_dump(buf_out, sizeof(buf_out), OD_WIDTH_DEFAULT);
    
    sdcard_fs_write(filename, (char *) buf_out, sizeof(buf_out));

    // // Free the dynamically allocated memory
    // free(cipher_text);

    return;
}
