#ifndef SEC_GCOAP_DTLS_H
#define SEC_GCOAP_DTLS_H

#include "fmt.h"
#include "net/gcoap.h"
#include "net/utils.h"
#include "od.h"

#include "net/credman.h"
#include "net/dsm.h"
#include "tinydtls_keys.h"
#define PSK_OPTIONS "i:k:"
#define PSK_ID_MAXLEN 32
#define PSK_MAXLEN 32

/* Example credential tag for credman. Tag together with the credential type needs to be unique. */
#define GCOAP_DTLS_CREDENTIAL_TAG 10

void sec_gcoap_dtls_init(void);

#endif /* SEC_GCOAP_DTLS_H */
