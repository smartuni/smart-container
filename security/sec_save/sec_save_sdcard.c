#include "sdcard.h"

int init_sec_save_sdcard(void)
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