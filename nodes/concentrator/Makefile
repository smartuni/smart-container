# name of your application
APPLICATION = concentrator

# This is the target board for the Concentrator
BOARD ?= nrf52840dk
FEATURES_REQUIRED += periph_spi
# enable this for testing on the small feather board
# BOARD = feather-nrf52840
USEMODULE+=ztimer_sec
# This USEMODULE should be used if LORAWAN Board is connected to nrf52840dk board!!
ifeq ($(BOARD),nrf52840dk)
  USEMODULE += sx1272
endif

ifeq ($(BOARD),feather-nrf52840)
  # SPI parameters for nrf52840
  CFLAGS += -DSDCARD_SPI_PARAM_SPI_MODE=0
  CFLAGS += -DSDCARD_SPI_PARAM_CS=GPIO_PIN\(0,10\)
  CFLAGS += -DSDCARD_SPI_PARAM_CLK=GPIO_PIN\(0,14\)
  CFLAGS += -DSDCARD_SPI_PARAM_MOSI=GPIO_PIN\(0,13\)
  CFLAGS += -DSDCARD_SPI_PARAM_MISO=GPIO_PIN\(0,15\)
endif

CFLAGS += -DEVENT_THREAD_MEDIUM_STACKSIZE=1024
CFLAGS += -DISR_STACKSIZE=1024

# For development environment
QUIET ?= 1
DEVELHELP ?= 1
CFLAGS += -DPROVISIONING_ENABLE_DEV=1
CFLAGS += -DPROVISIONING_CONFIG_CONCENTRATOR

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../RIOT

# Add project base for custom includes
PROJECTBASE ?= $(CURDIR)/..

$(info $(PROJECTBASE))


# Add modules directory for custom modules
EXTERNAL_MODULE_DIRS += $(PROJECTBASE)/modules
USEMODULE += cycling_buffer

# Provisioning modules
include $(CURDIR)/Makefile.provisioning_helper
include $(CURDIR)/Makefile.sec_link_layer
include $(CURDIR)/Makefile.sec_save

# enable default networking devices in the platform
USEMODULE += netdev_default

# automatically initialize network interfaces for enabled devices
USEMODULE += auto_init_gnrc_netif

# add minimal IPv6 support
USEMODULE += gnrc_ipv6_default

# add CoAP module
USEMODULE += log_color
USEMODULE += random 
USEMODULE += fmt
USEMODULE += od
USEMODULE += shell
USEMODULE += gcoap
USEMODULE += od
USEMODULE += senml_cbor


# Add support for GNRC LoRaWAN (v1.0.3)
USEMODULE += gnrc_lorawan

# Add event queue/threads
USEMODULE += event_periodic_callback
USEMODULE += event_thread

# Tell GNRC to encode LoRaWAN port in the GNRC netif header.
# This allows us to use `gnrc_txtsnd` to send data from the shell using the
# `txtsnd` command.
# Note: From Release 22.01 all GNRC LoRaWAN packets will include the netif
# header. Therefore this flag will be removed after that

CFLAGS += -DCONFIG_GNRC_NETIF_LORAWAN_NETIF_HDR

#
# Set region
CFLAGS += -DCONFIG_LORAMAC_REGION_EU_868
#
# If commented, the default value (DR0) is used. Note this value is also used for the OTAA.
CFLAGS += -DCONFIG_LORAMAC_DEFAULT_DR_5

# CFLAGS += -DCONFIG_GNRC_IPV6_NIB_SLAAC
# add ztimer module
USEMODULE += ztimer

ifdef DBG_ID_COAP
  DEBUG_ADAPTER_ID=$(DBG_ID_COAP)
  PORT=/dev/ttyACM1
endif

#possibly useless includes

USEMODULE += periph_gpio

# add ICMPv6 support (ping)
USEMODULE += gnrc_icmpv6_echo

# object dump allows use to print streams of bytes
USEMODULE += od

# fmt allows use to format strings
USEMODULE += fmt

USEMODULE += netutils
# Add also the shell, some shell commands
USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += ps

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1
CFLAGS += -I$(CURDIR)

include $(RIOTBASE)/Makefile.include

CFLAGS ?= -DLOG_LEVEL=LOG_ALL
