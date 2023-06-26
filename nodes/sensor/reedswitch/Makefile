# name of your application
APPLICATION = reedswitch_node

# If no BOARD is found in the environment, use this default:
BOARD ?= feather-nrf52840

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../../RIOT
PROJECT_BASE ?= $(CURDIR)/../..

USEMODULE += ztimer
USEMODULE += ztimer_msec

# Include external CoAP module
EXTERNAL_MODULE_DIRS += $(PROJECT_BASE)/modules
USEMODULE += coap

USEMODULE += mtd
USEMODULE += mtd_flashpage
USEMODULE += cipher_modes
#USEMODULE += ieee802154_security
USEMODULE += crypto_aes_128
USEMODULE += periph_gpio
USEMODULE += periph_gpio_irq

# Includes used by coap.h have to be included again
USEMODULE += netdev_default
USEMODULE += auto_init_gnrc_netif
USEMODULE += gnrc_ipv6_default
USEMODULE += gnrc_icmpv6_echo
USEMODULE += gcoap
USEMODULE += netutils
USEMODULE += od
USEMODULE += senml

include $(RIOTBASE)/Makefile.include
