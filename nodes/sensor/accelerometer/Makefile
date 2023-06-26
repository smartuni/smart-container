# name of application
APPLICATION = accelerometer

BOARD ?= feather-nrf52840

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../../RIOT
PROJECT_BASE ?= $(CURDIR)/../..

# Include external CoAP module
EXTERNAL_MODULE_DIRS += $(PROJECT_BASE)/modules
USEMODULE += coap

USEMODULE += mtd
USEMODULE += mtd_flashpage
USEMODULE += cipher_modes
USEMODULE += ieee802154_security
USEMODULE += crypto_aes_128

# Sensordriver
USEMODULE += lis2dh12_i2c
USEMODULE += lis2dh12_int

# GPIO for interrupt pin
USEMODULE += periph_gpio

# Be able to use interrupts
USEMODULE += periph_gpio_irq

# include timer
USEMODULE += ztimer_sec

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