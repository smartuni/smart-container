#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "shell.h"
#include "test_utils/expect.h"
#include "periph/eeprom.h"

#ifndef BUFFER_SIZE
#define BUFFER_SIZE     (42U)
#endif

static char buffer[BUFFER_SIZE + 1];

static int cmd_info(int argc, char **argv)
{
    (void)argc;
    (void)argv;

#ifdef EEPROM_START_ADDR
    printf("EEPROM start addr:\t0x%08x\n", (int)EEPROM_START_ADDR);
#endif
    printf("EEPROM size:\t\t%i\n", (int)EEPROM_SIZE);

    return 0;
}

static int cmd_read(int argc, char **argv)
{
    if (argc < 3) {
        printf("usage: %s <pos> <count>\n", argv[0]);
        return 1;
    }

    uint32_t pos = atoi(argv[1]);
    uint8_t count = atoi(argv[2]);

    if (!count) {
        puts("Count should be greater than 0");
        return 1;
    }

    if (count > BUFFER_SIZE) {
        puts("Count exceeds buffer size");
        return 1;
    }

    if (pos + count > EEPROM_SIZE) {
        puts("Failed: cannot read out of eeprom bounds");
        return 1;
    }

    size_t ret = eeprom_read(pos, (uint8_t *)buffer, count);
    buffer[count] = '\0';

    printf("Data read from EEPROM (%d bytes): %s\n", (int)ret, buffer);

    return 0;
}

static int cmd_read_byte(int argc, char **argv)
{
    if (argc < 2) {
        printf("usage: %s <pos>\n", argv[0]);
        return 1;
    }

    uint32_t pos = atoi(argv[1]);

    if (pos >= EEPROM_SIZE) {
        puts("Failed: cannot read out of eeprom bounds");
        return 1;
    }

    uint8_t byte = eeprom_read_byte(pos);
    printf("Byte read from EEPROM: 0x%02X (%c)\n", byte, byte);

    return 0;
}

static int cmd_write(int argc, char **argv)
{
    if (argc < 3) {
        printf("usage: %s <pos> <data>\n", argv[0]);
        return 1;
    }

    uint32_t pos = atoi(argv[1]);

    if (pos + strlen(argv[2]) > EEPROM_SIZE) {
        puts("Failed: cannot write out of eeprom bounds");
        return 1;
    }

    size_t ret = eeprom_write(pos, (uint8_t *)argv[2], strlen(argv[2]));
    printf("%d bytes written to EEPROM\n", (int)ret);

    return 0;
}

static int cmd_write_byte(int argc, char **argv)
{
    if (argc < 3) {
        printf("usage: %s <pos> <byte>\n", argv[0]);
        return 1;
    }

    uint32_t pos = atoi(argv[1]);

    if (pos >= EEPROM_SIZE) {
        puts("Failed: cannot write out of eeprom bounds");
        return 1;
    }

    eeprom_write_byte(pos, *(uint8_t *)argv[2]);
    printf("Byte written to EEPROM\n");

    return 0;
}

static int cmd_set
