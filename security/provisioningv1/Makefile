# Name of your application
APPLICATION = provisioning

# If no BOARD is found in the environment, use this default:
PORT=/dev/ttyS6
BOARD ?= feather-nrf52840

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../RIOT

# Import necessary modules
USEMODULE += xtimer
USEMODULE += od
USEMODULE += semtech_loramac_rx
USEMODULE += periph_uart
USEMODULE += periph_flashpage
USEMODULE += shell_cmds_default  # Provides reboot command
USEMODULE += log  # Include the log module
USEMODULE += fmt
USEMODULE += fmt_hexdump
USEMODULE += periph_pm
# Include the Semtech LoRaMAC package
USEPKG += semtech-loramac

# Required features
FEATURES_REQUIRED += periph_uart
FEATURES_REQUIRED += periph_flashpage

# Comment this out to disable code in RIOT that does safety checking
# Which is not needed in a production environment but helps in the
# Development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1


# Include the base RIOT Makefile
include $(RIOTBASE)/Makefile.include
