#ifndef SEC_LINK_LAYER_H
#define SEC_LINK_LAYER_H

#include "thread.h"
#include "shell.h"
#include "crypto/ciphers.h"
#include "net/ieee802154_security.h"
#include "net/gnrc/pktdump.h"
#include "net/gnrc/netif.h"
#include "net/gnrc.h"
#include "log.h"
#include "od.h"

void sec_link_layer_init(ieee802154_sec_context_t *link_layer_sec_ctx);

#endif // SEC_LINK_LAYER_H