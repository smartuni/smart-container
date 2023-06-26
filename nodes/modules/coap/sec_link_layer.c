#include "thread.h"
#include "shell.h"
#include "crypto/ciphers.h"
#include "net/ieee802154_security.h"
#include "net/gnrc/pktdump.h"
#include "net/gnrc/netif.h"
#include "net/gnrc.h"
#include "log.h"
#include "od.h"

#include "sec_link_layer.h"
#include "provisioning_helper.h"

void sec_link_layer_init(ieee802154_sec_context_t *link_layer_sec_ctx)
{
    uint8_t link_layer_security_key[IEEE802154_SEC_KEY_LENGTH];
    provisioning_helper_get_ieee802154_security_key(link_layer_security_key);
    LOG_INFO("Provisioned IEEE 802.15.4 security key is: %x%x %x%x %x%x %x%x %x%x %x%x %x%x %x%x\n", link_layer_security_key[0], link_layer_security_key[1], link_layer_security_key[2], link_layer_security_key[3], 
        link_layer_security_key[4], link_layer_security_key[5], link_layer_security_key[6], link_layer_security_key[7],
        link_layer_security_key[8], link_layer_security_key[9], link_layer_security_key[10], link_layer_security_key[11],
        link_layer_security_key[12], link_layer_security_key[13], link_layer_security_key[14], link_layer_security_key[15]);

    ieee802154_sec_init(link_layer_sec_ctx);
    cipher_init(&(link_layer_sec_ctx->cipher), CIPHER_AES, link_layer_security_key, IEEE802154_SEC_KEY_LENGTH);
    
    LOG_INFO("security_level = %d\n", link_layer_sec_ctx->security_level);
    LOG_INFO("key_id_mode = %d\n", link_layer_sec_ctx->key_id_mode);
    LOG_INFO("key_index = %d\n", link_layer_sec_ctx->key_index);
    LOG_INFO("key_source: \n");
    od_hex_dump(&(link_layer_sec_ctx->key_source), IEEE802154_LONG_ADDRESS_LEN, OD_WIDTH_DEFAULT);
    LOG_INFO("frame_counter = %ld\n",link_layer_sec_ctx->frame_counter);
}
