# name of application
APPLICATION = bme280Test

# If no BOARD is found in the environment, use this default:
BOARD ?= nucleo-l152re

# Absolute Path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../RIOT

# Use saul
USEMODULE += saul
USEMODULE += saul_default

# Include BME280 via I2C
USEMODULE += bme280_i2c

# Specify default I2C device and address
# Address is 0x76 or 0x77
CFLAGS += -DBMX280_PARAM_I2C_DEV=I2C_DEV\(0\)
CFLAGS += -DBMX280_PARAM_i2C_ADDR=0x77

# Use timer to read periodically
USEMODULE += ztimer
USEMODULE += ztimer_msec

include $(RIOTBASE)/Makefile.include