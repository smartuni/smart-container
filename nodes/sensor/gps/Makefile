# Set the name of your application:
APPLICATION = gps
 
# If no BOARD is found in the environment, use this default:
BOARD ?= feather-nrf52840
 
FEATURES_REQUIRED += periph_uart
FEATURES_OPTIONAL += periph_lpuart  # STM32 L0 and L4 provides lpuart support
FEATURES_OPTIONAL += periph_uart_collision
FEATURES_OPTIONAL += periph_uart_modecfg
FEATURES_OPTIONAL += periph_uart_rxstart_irq

USEPKG += minmea
USEPKG += nanocbor

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../../RIOT
PROJECT_BASE ?= $(CURDIR)/../..

# If no BOARD is found in the environment, use this default:
BOARD ?= feather-nrf52840

USEMODULE += fmt
USEMODULE += ztimer_sec
USEMODULE += netdev_default
USEMODULE += auto_init_gnrc_netif
USEMODULE += gnrc_ipv6_default
USEMODULE += gnrc_icmpv6_echo
USEMODULE += gcoap
USEMODULE += netutils
USEMODULE += od
USEMODULE += senml

EXTERNAL_MODULE_DIRS += $(PROJECT_BASE)/modules
USEMODULE += coap

USEMODULE += mtd
USEMODULE += mtd_flashpage
USEMODULE += cipher_modes
USEMODULE += ieee802154_security
USEMODULE += crypto_aes_128

# avoid running Kconfig by default
SHOULD_RUN_KCONFIG ?=
 
include $(RIOTBASE)/Makefile.include
