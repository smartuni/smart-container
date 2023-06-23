# LDFLAGS="-L/usr/local/opt/openssl@1.1/lib"
# CPPFLAGS="-I/usr/local/opt/openssl@1.1/include"

# name of your application
APPLICATION = sec_save
BOARD = feather-nrf52840


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

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

include $(RIOTBASE)/Makefile.include

CFLAGS ?= -DLOG_LEVEL=LOG_ALL
