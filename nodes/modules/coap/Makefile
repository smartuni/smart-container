RIOTBASE ?= $(CURDIR)/RIOT
include $(RIOTBASE)/Makefile.base

# enable default networking devides in the platform
USEMODULE += netdev_default

# automatically initialize network interfaces for enabled devices
USEMODULE += auto_init_gnrc_netif

# add minimal IPv6 support
USEMODULE += gnrc_ipv6_default

# add ICMPv6 support (ping)
USEMODULE += gnrc_icmpv6_echo

# add CoAP module
USEMODULE += gcoap

# object dump allows use to print streams of bytes
USEMODULE += od

# fmt allows use to format strings
USEMODULE += fmt

USEMODULE += netutils

# provisioning_helper
USEMODULE += mtd
USEMODULE += mtd_flashpage

CFLAGS += -DPROVISIONING_ENABLE_DEV=1
CFLAGS += -DPROVISIONING_CONFIG_CONCENTRATOR

# sec_link_layer
USEMODULE += cipher_modes
USEMODULE += crypto_aes_128

USEMODULE += ieee802154
#USEMODULE += ieee802154_security
USEMODULE += gnrc_netif_ieee802154
USEMODULE += gnrc_netif
USEMODULE += netdev_default

# Modules to include:
USEMODULE += shell_cmds_default
USEMODULE += ps

# allow to use a smaller packet buffer in low-PDU drivers
ifdef GNRC_PKTBUF_SIZE
  CFLAGS += -DCONFIG_GNRC_PKTBUF_SIZE=$(GNRC_PKTBUF_SIZE)
endif

# gnrc is a meta module including all required, basic gnrc networking modules
USEMODULE += gnrc

# automatically initialize the network interface
USEMODULE += auto_init_gnrc_netif

# shell command to send L2 packets with a simple string
USEMODULE += gnrc_txtsnd

# the application dumps received packets to stdout
USEMODULE += gnrc_pktdump

CFLAGS += -DCONFIG_IEEE802154_SEC_DEFAULT_KEY=\"29DJ29XL8D3Q7QXG\"

# # Set a custom channel if needed
# include $(RIOTMAKE)/default-radio-settings.inc.mk
