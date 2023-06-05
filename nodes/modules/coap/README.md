# CoAP Module for Nodes Team
This module lets nodes use it to send data to the concentrator.

## Usage
Add this module to your project by adding following lines to your Makefile (it is assumed that you placed your project into the `nodes/sensor` folder):
```make
# nodes team base directory
PROJECT_BASE ?= $(CURDIR)/../..
EXTERNAL_MODULE_DIRS += $(PROJECT_BASE)/modules
USEMODULE += coap
```