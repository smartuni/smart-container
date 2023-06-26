APPLICATION = ieee802154_security
BOARD = feather-nrf52840

ifneq (,$(wildcard $(CURDIR)/tests*/.))
  # add interactive test configuration when testing Kconfig
  DEFAULT_MODULE += test_utils_interactive_sync
  # add stack metric printing configuration when testing Kconfig
  DEFAULT_MODULE += test_utils_print_stack_usage

  # do the same for Kconfig builds
  ifeq (1,$(TEST_KCONFIG))
    KCONFIG_ADD_CONFIG += $(RIOTBASE)/tests/test_utils.config
  endif
endif

CFLAGS += -DPROVISIONING_ENABLE_DEV=1
CFLAGS += -DPROVISIONING_CONFIG_CONCENTRATOR

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../RIOT
QUIET ?= 1
DEVELHELP ?= 1

# Provisioning modules
USEMODULE += mtd
USEMODULE += mtd_flashpage

USEMODULE += od
USEMODULE += log_color

USEMODULE += cipher_modes
USEMODULE += crypto_aes_128

USEMODULE += ieee802154
USEMODULE += ieee802154_security
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

include $(RIOTBASE)/Makefile.include

# Set a custom channel if needed
include $(RIOTMAKE)/default-radio-settings.inc.mk