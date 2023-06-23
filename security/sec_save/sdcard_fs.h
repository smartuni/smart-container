#ifndef SDCARD_FS_H
#define SDCARD_FS_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include "log.h"
#include "mtd.h"
#include "fatfs_diskio_mtd.h"
#include "shell.h"
#include "mtd_sdcard.h"
#include "sdcard_spi_params.h"

#define TEST_FATFS_READ_BUFFER_SIZE 64
#define TEST_FATFS_MAX_LBL_SIZE 64
#define TEST_FATFS_MAX_VOL_STR_LEN 14 /* "-2147483648:/\0" */
#define TEST_FATFS_FIXED_SECTOR_SIZE 512
#define TEST_FATFS_FATENT_OFFSET 2
#define TEST_FATFS_SHIFT_B_TO_GIB 30
#define TEST_FATFS_SHIFT_B_TO_MIB 20
#define TEST_FATFS_RTC_MON_OFFSET 1
#define TEST_FATFS_RTC_YEAR 2000
#define TEST_FATFS_RTC_MON  1
#define TEST_FATFS_RTC_DAY  1
#define TEST_FATFS_RTC_H    0
#define TEST_FATFS_RTC_M    0
#define TEST_FATFS_RTC_S    0
#define IEC_KIBI 1024
#define SI_KILO 1000

/* Function prototypes */
void sdcard_fs_init(void);
int _mount(void);
int _ls(void);
int sdcard_fs_write(char *buf, uint32_t buf_len);

#endif /* SDCARD_FS_H */
/** @} */