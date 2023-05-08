#include "stdint.h"

#include "periph/eeprom.h"
#include "crypto/ciphers.h"
#include "phydat.h"
#include "sdcard_spi.h"
#include "sdcard_spi_internal.h"
#include "sdcard_spi_params.h"

#include "sec_save.h"

#define AES_KEY_EEPROM_ADDRESS 0x0f
#define AES_KEY_SIZE 16
#define AES_BLOCK_SIZE 16
#define SERIALIZED_PHYDAT_SIZE 512
#define SERIALIZED_PHYDAT_DIM 1

/* independent of what you specify in a r/w cmd this is the maximum number of blocks read at once.
   If you call read with a bigger blockcount the read is performed in chunks*/
#define MAX_BLOCKS_IN_BUFFER 4
#define BLOCK_PRINT_BYTES_PER_LINE 16
#define FIRST_PRINTABLE_ASCII_CHAR 0x20
#define ASCII_UNPRINTABLE_REPLACEMENT "."

/* this is provided by the sdcard_spi driver
 * see drivers/sdcard_spi/sdcard_spi.c */
extern sdcard_spi_t sdcard_spi_devs[ARRAY_SIZE(sdcard_spi_params)];
extern sdcard_spi_t *card = &sdcard_spi_devs[0];

uint8_t sdcard_buffer[SD_HC_BLOCK_SIZE * MAX_BLOCKS_IN_BUFFER];

/*************************************************************
 * EEPROM functions
 ************************************************************/
static int read_aes_key(uint8_t *key)
{
    if (eeprom_read(AES_KEY_EEPROM_ADDRESS, key, AES_KEY_SIZE) != AES_KEY_SIZE)
    {
        return -1;
    }
    return 1;
}

/*************************************************************
 * Serialization functions
 ************************************************************/
static size_t serialize_phydat(uint8_t *serialized_phydat, const phydat_t *phydat)
{
    size_t serialized_phydat_size = phydat_to_json(phydat, SERIALIZED_PHYDAT_DIM, serialized_phydat);

    if (serialized_phydat_size > SERIALIZED_PHYDAT_SIZE)
    {
        return -1;
    }

    return serialized_phydat_size;
}

/*************************************************************
 * Encryption functions
 ************************************************************/
static int encrypt_buf(uint8_t *key, uint8_t *plain_text, uint8_t *cipher_text)
{
    cipher_t cipher;

    if (cipher_init(&cipher, CIPHER_AES, key, AES_KEY_SIZE) < 0)
    {
        return -1;
    }

    unsigned int i;
    for (i = 0; i < sizeof(plain_text) / AES_BLOCK_SIZE; ++i)
    {
        if (cipher_encrypt(&cipher, plain_text + i * AES_BLOCK_SIZE, cipher_text + i * AES_BLOCK_SIZE) < 0)
        {
            return -1;
        }
    }

    return 1;
}

/*************************************************************
 * SD Card SPI Driver functions
 ************************************************************/
static int init_sdcard(void)
{
    fprintf(PRINT_FILE, "Initializing SD-card at SPI_%i...", sdcard_spi_params[0].spi_dev);

    if (sdcard_spi_init(card, &sdcard_spi_params[0]) != 0)
    {
        fprintf(PRINT_FILE, "[FAILED]");
        fprintf(PRINT_FILE, "enable debugging in sdcard_spi.c for more information!");
        return -2;
    }
    fprintf(PRINT_FILE, "[OK]");
    return 0;
}

static int write_sdcard(int bladdr, int data, size_t data_len)
{
    int bladdr;
    char *data;
    int size;
    bool repeat_data = false;

    if (argc == 3 || argc == 4)
    {
        bladdr = atoi(argv[1]);
        data = argv[2];
        size = strlen(argv[2]);
        printf("will write '%s' (%d chars) at start of block %d\n", data, size, bladdr);
        if (argc == 4 && (strcmp("-r", argv[3]) == 0))
        {
            repeat_data = true;
            puts("the rest of the block will be filled with copies of that string");
        }
        else
        {
            puts("the rest of the block will be filled with zeros");
        }
    }
    else
    {
        printf("usage: %s blockaddr string [-r]\n", argv[0]);
        return -1;
    }

    if (size > SD_HC_BLOCK_SIZE)
    {
        printf("maximum stringsize to write at once is %d ...aborting\n", SD_HC_BLOCK_SIZE);
        return -1;
    }

    /* copy data to a full-block-sized buffer an fill remaining block space according to -r param*/
    uint8_t write_buffer[SD_HC_BLOCK_SIZE];
    for (unsigned i = 0; i < sizeof(write_buffer); i++)
    {
        if (repeat_data || ((int)i < size))
        {
            write_buffer[i] = data[i % size];
        }
        else
        {
            write_buffer[i] = 0;
        }
    }

    sd_rw_response_t state;
    int chunks_written = sdcard_spi_write_blocks(card, bladdr, write_buffer, SD_HC_BLOCK_SIZE, 1, &state);

    if (state != SD_RW_OK)
    {
        printf("write error %d (wrote %d/%d blocks)\n", state, chunks_written, 1);
        return -1;
    }

    printf("write block %d [OK]\n", bladdr);
    return 0;
}
#TODO

/*************************************************************
 * sec_save
 ************************************************************/
int sec_save(phydat_t *phydat)
{
    size_t serialized_phydat_size = 0;
    uint8_t serialized_phydat[SERIALIZED_PHYDAT_SIZE] = {0};

    // Serialize data struct in data buffer
    serialized_phydat_size = serialize_phydat(&serialized_phydat, phydat);
    if (serialized_phydat_size < 0)
    {
        return -1;
    }

    // Encrypt serialized data buffer
    uint8_t key[AES_KEY_SIZE] = {0};
    uint8_t plain_text[SERIALIZED_PHYDAT_SIZE] = {0};
    uint8_t cipher_text[SERIALIZED_PHYDAT_SIZE] = {0};

    if (read_aes_key(&key) < 0)
    {
        return -1;
    }

    if (encrypt_buf(&key, &plain_text, &cipher_text) < 0)
    {
        return -1;
    }

    // Persist data in SD card
    init_sdcard(void);

    sd_rw_response_t state;
    int chunks_written = sdcard_spi_write_blocks(card, bladdr, write_buffer, SD_HC_BLOCK_SIZE, 1, &state);

    if (state != SD_RW_OK)
    {
        printf("write error %d (wrote %d/%d blocks)\n", state, chunks_written, 1);
        return -1;
    }
}