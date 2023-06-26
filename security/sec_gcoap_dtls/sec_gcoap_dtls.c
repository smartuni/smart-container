#include "provisioning_helper.h"
#include "sec_gcoap_dtls.h"

void sec_gcoap_dtls_init(void)
{
    static uint8_t psk_id_0[PROVISIONING_FLASH_LEN_DEVICE_ID];
    static uint8_t psk_key_0[PROVISIONING_FLASH_LEN_DTLS_PSK_AES_KEY];

    provisioning_helper_get_psk_id_key(psk_id_0, psk_key_0);

    static const credman_credential_t credential = {
        .type = CREDMAN_TYPE_PSK,
        .tag = GCOAP_DTLS_CREDENTIAL_TAG,
        .params = {
            .psk = {
                .key = { .s = psk_key_0, .len = sizeof(psk_key_0), },
                .id = { .s = psk_id_0, .len = sizeof(psk_id_0), },
            }
        },
    };
    
    int res = credman_add(&credential);
    if (res < 0 && res != CREDMAN_EXIST) {
        /* ignore duplicate credentials */
        printf("gcoap: cannot add credential to system: %d\n", res);
        return;
    }
    sock_dtls_t *gcoap_sock_dtls = gcoap_get_sock_dtls();
    res = sock_dtls_add_credential(gcoap_sock_dtls, GCOAP_DTLS_CREDENTIAL_TAG);
    if (res < 0) {
        printf("gcoap: cannot add credential to DTLS sock: %d\n", res);
    }
}