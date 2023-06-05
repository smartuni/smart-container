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
