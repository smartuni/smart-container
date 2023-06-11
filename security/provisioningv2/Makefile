# Name of your application
APPLICATION = provisioning

# Target board
BOARD ?= pba-d-01-kw2x

# Required features
FEATURES_REQUIRED += periph_eeprom
USEMODULE += shell_cmds_default  # provides reboot command

# Absolute path to the RIOT base directory
#RIOTBASE ?= /home/salman/IE6/RIOT
RIOTBASE ?= $(CURDIR)/../../RIOT

.PHONY: all generate_key clean

KEY_OUTPUT := $(shell mktemp -u keyXXXXX.hex)
C_KEY_OUTPUT := psk_key.c
BUILD_TARGET := main # replace this with the actual name of your build target

generate_key: $(KEY_OUTPUT)

$(KEY_OUTPUT):
	python3 generate_key.py

$(C_KEY_OUTPUT): $(KEY_OUTPUT)
	echo "#include <stdint.h>" > $@
	echo "uint8_t psk_key[16] = {" >> $@
	sed 's/../0x&, /g' < $< | tr '\n' ' ' | sed 's/, $$//' >> $@
	echo "};" >> $@

$(BUILD_TARGET): $(C_KEY_OUTPUT)
	$(MAKE) -f Makefile.original # replace this with the actual command to build your project

all: generate_key $(C_KEY_OUTPUT) $(BUILD_TARGET) clean

clean:
	rm -f $(KEY_OUTPUT)

# Include the base RIOT Makefile
include $(RIOTBASE)/Makefile.include
