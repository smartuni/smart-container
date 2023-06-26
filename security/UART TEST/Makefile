# name of your application
APPLICATION = UART


BOARD = feather-nrf52840
PORT=/dev/tty.usbmodem143101



# Include modules
USEMODULE += periph_uart
# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../RIOT

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1


FEATURES_REQUIRED += periph_uart
# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

include $(RIOTBASE)/Makefile.include
