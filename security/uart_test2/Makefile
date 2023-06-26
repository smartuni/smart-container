# Name of your application
APPLICATION = provisioning

# If no BOARD is found in the environment, use this default:
<<<<<<< HEAD:security/uart_test 2/Makefile
PORT=/dev/tty.usbmodem14201
=======
PORT=/dev/ttyS6
>>>>>>> b19a1d7b3ac75e61210ac9dad0fdf681aa1abb6c:security/uart_test_v3/Makefile
BOARD ?= feather-nrf52840

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../RIOT
<<<<<<< HEAD:security/uart_test 2/Makefile
# USEMODULE_INCLUDES += $(RIOTBASE)/sys/log_printfnoformat/include

FEATURES_REQUIRED = periph_uart
USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += ps
USEMODULE += xtimer
USEMODULE += stdio_cdc_acm
=======

# Import necessary modules
USEMODULE += xtimer
USEMODULE += od
USEMODULE += periph_uart
USEMODULE += periph_flashpage
USEMODULE += shell_cmds_default  # Provides reboot command
USEMODULE += log  # Include the log module
USEMODULE += periph_pm
>>>>>>> b19a1d7b3ac75e61210ac9dad0fdf681aa1abb6c:security/uart_test_v3/Makefile

# Required features
#FEATURES_REQUIRED += periph_uart
#FEATURES_REQUIRED += periph_flashpage

# Comment this out to disable code in RIOT that does safety checking
# Which is not needed in a production environment but helps in the
# Development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1


# Include the base RIOT Makefile
include $(RIOTBASE)/Makefile.include
INCLUDES += -I$(APPDIR)
