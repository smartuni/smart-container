# name of application
APPLICATION = bme280

# If no BOARD is found in the environment, use this default:
BOARD ?= feather-nrf52840

# Absolute Path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../../../RIOT
PROJECT_BASE ?= $(CURDIR)/../../..

# Include external CoAP module
EXTERNAL_MODULE_DIRS += $(PROJECT_BASE)/modules
USEMODULE += coap

# Security modules
USEMODULE += mtd
USEMODULE += mtd_flashpage
USEMODULE += cipher_modes
USEMODULE += ieee802154_security
USEMODULE += crypto_aes_128

# Conversion from uint to string
USEMODULE += fmt

# Includes used by coap.h have to be included again
USEMODULE += netdev_default
USEMODULE += auto_init_gnrc_netif
USEMODULE += gnrc_ipv6_default
USEMODULE += gnrc_icmpv6_echo
USEMODULE += gcoap
USEMODULE += netutils
USEMODULE += od
USEMODULE += senml

# Use saul
USEMODULE += saul
USEMODULE += saul_default

# Include BME280 via I2C
USEMODULE += bme280_i2c

# Specify default I2C device and address
# Address is 0x76 or 0x77
CFLAGS += -DBMX280_PARAM_I2C_DEV=I2C_DEV\(0\)
CFLAGS += -DBMX280_PARAM_i2C_ADDR=0x77

# Use timer to read periodically
USEMODULE += ztimer
USEMODULE += ztimer_sec

include $(RIOTBASE)/Makefile.include