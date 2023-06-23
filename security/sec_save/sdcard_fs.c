#include "sdcard_fs.h"

FATFS fat_fs; 

#define SDCARD_SPI_NUM ARRAY_SIZE(sdcard_spi_params)
/* sdcard devs are provided by drivers/sdcard_spi/sdcard_spi.c */
extern sdcard_spi_t sdcard_spi_devs[SDCARD_SPI_NUM];
mtd_sdcard_t mtd_sdcard_devs[SDCARD_SPI_NUM];
mtd_dev_t *fatfs_mtd_devs[SDCARD_SPI_NUM];

#define MTD_NUM ARRAY_SIZE(fatfs_mtd_devs)

void sdcard_fs_init(void)
{
    for (unsigned int i = 0; i < SDCARD_SPI_NUM; i++){
        mtd_sdcard_devs[i].base.driver = &mtd_sdcard_driver;
        mtd_sdcard_devs[i].sd_card = &sdcard_spi_devs[i];
        mtd_sdcard_devs[i].params = &sdcard_spi_params[i];
        fatfs_mtd_devs[i] = &mtd_sdcard_devs[i].base;

        if(mtd_init(&mtd_sdcard_devs[i].base) == 0) {
            printf("init sdcard_mtd %u [OK]\n", i);
        }else{
            printf("init sdcard_mtd %u [FAILED]\n", i);
        }
    }

    _mount();
    _ls();
}

int _mount(void)
{
    LOG_INFO("mounting file system image...");

    char volume_str[] = "0:/";

    /* "0:/" points to the root dir of drive 0 */
    FRESULT mountresu = f_mount(&fat_fs, volume_str, 1);
    TCHAR label[TEST_FATFS_MAX_LBL_SIZE];

    if (mountresu == FR_OK) {
        puts("[OK]");
        if (f_getlabel("", label, NULL) == FR_OK) {
            printf("Volume name: %s\n", label);
        }

        FATFS *fs;
        DWORD fre_clust;

        /* Get volume information and free clusters of selected drive */
        if (f_getfree(volume_str, &fre_clust, &fs) != FR_OK) {
            puts("wasn't able to get volume size info!");
        }
        else {

            #if FF_MAX_SS == FF_MIN_SS
            uint16_t sector_size = TEST_FATFS_FIXED_SECTOR_SIZE;
            #else
            uint16_t sector_size = fs->ssize;
            #endif

            uint64_t total_bytes = (fs->n_fatent - TEST_FATFS_FATENT_OFFSET) * fs->csize;
            total_bytes *= sector_size;
            uint64_t free_bytes = fre_clust * fs->csize;
            free_bytes *= sector_size;

            uint32_t to_gib_i = total_bytes >> TEST_FATFS_SHIFT_B_TO_GIB;
            uint32_t to_gib_f = ((((total_bytes >> TEST_FATFS_SHIFT_B_TO_MIB) - to_gib_i * IEC_KIBI)
                                  * SI_KILO) / IEC_KIBI);

            uint32_t fr_gib_i = free_bytes >> TEST_FATFS_SHIFT_B_TO_GIB;
            uint32_t fr_gib_f = ((((free_bytes >> TEST_FATFS_SHIFT_B_TO_MIB) - fr_gib_i * IEC_KIBI)
                                  * SI_KILO) / IEC_KIBI);

            printf("%" PRIu32 ",%03" PRIu32 " GiB of %" PRIu32 ",%03" PRIu32
                   " GiB available\n", fr_gib_i, fr_gib_f, to_gib_i, to_gib_f);
        }
    }
    else {
        puts("[FAILED]");
        switch (mountresu) {
            case FR_NO_FILESYSTEM:
                puts("no filesystem -> you need to format the card to FAT");
                break;
            case FR_DISK_ERR:
                puts("error in the low-level disk driver!");
                break;
            default:
                printf("error %d -> see ff.h of fatfs package for "
                       "further d3etails\n", mountresu);
        }
        return -1;
    }
    return 0;
}

int _ls(void)
{
    char *path;
    FRESULT res;
    DIR dir;
    static FILINFO fno;

    path = "/";

    res = f_opendir(&dir, path);/* Open the directory */

    if (res == FR_OK) {
        while (true) {
            res = f_readdir(&dir, &fno);    /* Read a directory item */

            if ((res != FR_OK) || fno.fname[0] == 0) {
                break;                      /* Break on error or end of dir */
            }

            if (fno.fattrib & AM_DIR) {     /* if this element is a directory */
                printf("%s%s/\n", path, fno.fname);
            }
            else {
                printf("%s/%s\n", path, fno.fname);
            }
        }

        f_closedir(&dir);
        return 0;
    }

    printf("[FAILED] error %d\n", res);
    return -1;
}

int sdcard_fs_write(char *buf, uint32_t buf_len)
{
    // argv[1] = filename
    // argv[2] = string

    FIL fd;
    UINT bw;

    char *filename = "TEST.TXT";
    uint32_t len = buf_len;
    FRESULT open_resu = f_open(&fd, filename, FA_WRITE | FA_OPEN_APPEND);

    if (open_resu == FR_OK) {
        printf("writing %" PRId32 " bytes to %s ...", len, filename);
        FRESULT write_resu = f_write(&fd, buf, len, &bw);

        if ((write_resu != FR_OK) || (bw < len)) {
            printf("[FAILED] (f_write error %d)\n", write_resu);
            return -2;
        }
        else {
            FRESULT close_resu = f_close(&fd);

            if (close_resu == FR_OK) {
                puts("[OK]");
                return 0;
            }

            printf("[FAILED] (f_close error %d)\n", open_resu);
            return -3;
        }
    }

    printf("[FAILED] (f_open error %d)\n", open_resu);
    return -1;
}
