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

USEMODULE += fmt
USEMODULE += shell
USEMODULE += xtimer

# avoid running Kconfig by default
SHOULD_RUN_KCONFIG ?=

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../../RIOT
 
include $(RIOTBASE)/Makefile.include
