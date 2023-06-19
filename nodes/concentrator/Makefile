# name of your application
APPLICATION = concentrator

# This is the target board for the Concentrator
BOARD ?= nrf52840dk
# enable this for testing on the small feather board
BOARD = feather-nrf52840

# This USEMODULE should be used if LORAWAN Board is connected to nrf52840dk board!!
ifeq ($(BOARD),nrf52840dk)
  USEMODULE += sx1272
endif

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../RIOT

# enable default networking devices in the platform
USEMODULE += netdev_default

# automatically initialize network interfaces for enabled devices
USEMODULE += auto_init_gnrc_netif

# add minimal IPv6 support
USEMODULE += gnrc_ipv6_default

# add CoAP module
USEMODULE += gcoap

# Add support for GNRC LoRaWAN (v1.0.3)
USEMODULE += gnrc_lorawan

# Tell GNRC to encode LoRaWAN port in the GNRC netif header.
# This allows us to use `gnrc_txtsnd` to send data from the shell using the
# `txtsnd` command.
# Note: From Release 22.01 all GNRC LoRaWAN packets will include the netif
# header. Therefore this flag will be removed after that

CFLAGS += -DCONFIG_GNRC_NETIF_LORAWAN_NETIF_HDR

# We can reduce the size of the packet buffer for LoRaWAN, since there's no IP
# support. This will reduce RAM consumption.
# Set GNRC_PKTBUF_SIZE via CFLAGS if not being set via Kconfig.
ifndef CONFIG_GNRC_PKTBUF_SIZE
  CFLAGS += -DCONFIG_GNRC_PKTBUF_SIZE=512
endif
#
# Set region
CFLAGS += -DCONFIG_LORAMAC_REGION_EU_868
#
# If commented, the default value (DR0) is used. Note this value is also used for the OTAA.
CFLAGS += -DCONFIG_LORAMAC_DEFAULT_DR_5

# add ztimer module
USEMODULE += ztimer

# The default size of GCOAP_PDU_BUF_SIZE can be too small for the response
# from the RD server. Use a larger value if the client drops response packet
# from RD server.
CFLAGS += -DCONFIG_GCOAP_PDU_BUF_SIZE=512

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

include $(RIOTBASE)/Makefile.include
