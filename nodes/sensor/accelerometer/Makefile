# name of application
APPLICATION = accelerometer

BOARD ?= feather-nrf52840

RIOTBASE ?= $(CURDIR)/../../RIOT

USEMODULE += lis2dh12_i2c
USEMODULE += lis2dh12_int
USEMODULE += periph_gpio
USEMODULE += periph_gpio_irq
USEMODULE += ztimer_sec

include $(RIOTBASE)/Makefile.include