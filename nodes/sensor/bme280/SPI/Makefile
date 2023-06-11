# name of application
APPLICATION = bme280SPItest

# If no BOARD is found in the environment, use this default:
BOARD ?= nucleo-f103rb

# Absolute Path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../../../RIOT

# Use saul
USEMODULE += saul
USEMODULE += saul_default

# Include BME280 via I2C
USEMODULE += bme280_spi

# Specify default SPI Device and CS Pin
CFLAGS += -DBMX280_PARAM_SPI_DEV=SPI_DEV\(0\)
CFLAGS += -DBMX280_PARAM_CS=GPIO_PIN\(PORT_B,6\)

# Use timer to read periodically
USEMODULE += ztimer
USEMODULE += ztimer_msec

include $(RIOTBASE)/Makefile.include