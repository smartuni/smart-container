APPLICATION = sensor_node_waterleak

BOARD ?= feather-nrf52840

# nodes team base directory
PROJECT_BASE ?= $(CURDIR)/../..
RIOTBASE ?= $(CURDIR)/../../RIOT

EXTERNAL_MODULE_DIRS += $(PROJECT_BASE)/modules
USEMODULE += coap

# USEMODULE += saul
# USEMODULE += saul_default
# USEMODULE += saul_adc

# add coap dependencies
USEMODULE += netdev_default
USEMODULE += auto_init_gnrc_netif
USEMODULE += gnrc_ipv6_default
USEMODULE += gcoap
USEMODULE += od
USEMODULE += netutils

# add ztimer
USEMODULE += ztimer

include $(RIOTBASE)/Makefile.include