# Name of your application
APPLICATION = provisioning

# Target board
BOARD ?= pba-d-01-kw2x

# Required features

FEATURES_REQUIRED += periph_eeprom
USEMODULE += shell_cmds_default  # provides reboot command
# Absolute path to the RIOT base directory
RIOTBASE ?= $(CURDIR)/../../RIOT

# Add a custom target for generating the key
generate_key:
	python3 generate_key.py > key.hex

all: generate_key
	$(MAKE) -C $(RIOTBASE)

# Include the base RIOT Makefile
include $(RIOTBASE)/Makefile.include

