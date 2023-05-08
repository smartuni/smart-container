#ifndef SEC_SAVE_SDCARD_H
#define SEC_SAVE_SDCARD_H

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

int init_sec_save_sdcard(void);

#endif /* SEC_SAVE_SDCARD_H */
       /** @} */