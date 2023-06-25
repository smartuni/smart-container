# _  __  ____    _   _
# | |/ / |  _ \  | \ | |
# | ' /  | |_) | |  \| |
# | . \  |  __/  | |\  |
# |_|\_\ |_|     |_| \_|
#
# (c) 2018 KPN
# License: MIT license.
# Author: Jan Bogaerts
#
# base value example

import binascii
from kpn_senml import *
import time
import datetime
from cbor2 import loads, dumps, CBORTag


cbor_data = "81A4216B6465766963655F6E616D65006474656D70016343656C0214"
decoded_cbor_data = binascii.unhexlify(cbor_data)

json_data = loads(decoded_cbor_data)

print(decoded_cbor_data)
print(json_data[0][-2])