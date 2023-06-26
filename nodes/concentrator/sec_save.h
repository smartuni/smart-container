#ifndef SEC_SAVE_H
#define SEC_SAVE_H

#include "crypto/ciphers.h"
#include "log.h"
#include "od.h"

#include "sdcard_fs.h"
#include "provisioning_helper.h"

#define SEC_SAVE_ENC_BUFFER_SIZE 4096

void sec_save(const char *filename, const uint8_t *buf, size_t buf_len);

#endif /* SEC_SAVE_H */
/** @} */
