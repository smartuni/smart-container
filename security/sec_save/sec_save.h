#ifndef SEC_SAVE_H
#define SEC_SAVE_H

// #include <malloc.h>

#include "crypto/ciphers.h"
#include "log.h"
#include "od.h"

#include "sdcard_fs.h"
#include "provisioning_helper.h"

void sec_save(const char *filename, uint8_t *buf_out, uint8_t *buf, const size_t buf_len);

#endif /* SEC_SAVE_H */
/** @} */
