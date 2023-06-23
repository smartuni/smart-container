# LDFLAGS="-L/usr/local/opt/openssl@1.1/lib"
# CPPFLAGS="-I/usr/local/opt/openssl@1.1/include"

# name of your application
APPLICATION = sec_save
BOARD = feather-nrf52840

# Enable for concentrator only 
# CFLAGS += -DPROVISIONING_CONFIG_CONCENTRATOR

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

# General modules
USEMODULE += log_color
USEMODULE += random 
USEMODULE += fmt
USEMODULE += od
USEMODULE += shell

# Provisioning modules
USEMODULE += mtd
USEMODULE += mtd_flashpage

# Secure save modules
USEMODULE += cipher_modes
USEMODULE += crypto_aes_128
USEMODULE += phydat
# USEMODULE += sdcard_spi
USEMODULE += fatfs_diskio_mtd
USEMODULE += mtd_sdcard
USEPKG    += fatfs
FATFS_IMAGE_FILE_SIZE_MIB ?= 128

# Development environment only 
DEVELHELP ?= 1
QUIET ?= 1
# CFLAGS += -DPROVISIONING_ENABLE_DEV
# CFLAGS += -DENABLE_DEBUG=1

include $(RIOTBASE)/Makefile.include

# Must be after include $(RIOTBASE)/Makefile.include
CFLAGS ?= -DLOG_LEVEL=LOG_ALL
# CFLAGS += -DPROVISIONING_ENABLE_DEV
