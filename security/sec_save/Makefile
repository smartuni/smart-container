# LDFLAGS="-L/usr/local/opt/openssl@1.1/lib"
# CPPFLAGS="-I/usr/local/opt/openssl@1.1/include"

# name of your application
APPLICATION = sec_save
BOARD = feather-nrf52840

ifneq (,$(wildcard $(CURDIR)/tests*/.))
  # add interactive test configuration when testing Kconfig
  DEFAULT_MODULE += test_utils_interactive_sync
  # add stack metric printing configuration when testing Kconfig
  DEFAULT_MODULE += test_utils_print_stack_usage

  # do the same for Kconfig builds
  ifeq (1,$(TEST_KCONFIG))
    KCONFIG_ADD_CONFIG += $(RIOTBASE)/tests/test_utils.config
  endif
endif

# SPI parameters for nrf52840
CFLAGS += -DSDCARD_SPI_PARAM_SPI_MODE=0
CFLAGS += -DSDCARD_SPI_PARAM_CS=GPIO_PIN\(0,10\)
CFLAGS += -DSDCARD_SPI_PARAM_CLK=GPIO_PIN\(0,14\)
CFLAGS += -DSDCARD_SPI_PARAM_MOSI=GPIO_PIN\(0,13\)
CFLAGS += -DSDCARD_SPI_PARAM_MISO=GPIO_PIN\(0,15\)

FEATURES_OPTIONAL += periph_rtc
FEATURES_REQUIRED += periph_spi

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../RIOT

# For development environment
QUIET ?= 1
DEVELHELP ?= 1
CFLAGS += -DPROVISIONING_ENABLE_DEV=1
CFLAGS += -DPROVISIONING_CONFIG_CONCENTRATOR

# General modules
USEMODULE += log_color
USEMODULE += random 
USEMODULE += fmt
USEMODULE += od
USEMODULE += shell

# Provisioning modules
include $(CURDIR)/Makefile.provisioning_helper

# Link layer security modules
include $(CURDIR)/Makefile.link_layer_security

# Secure save modules
include $(CURDIR)/Makefile.sec_save


include $(RIOTBASE)/Makefile.include

CFLAGS ?= -DLOG_LEVEL=LOG_ALL
