from Crypto.Cipher import AES
from Crypto.Util.Padding import unpad
from binascii import unhexlify, hexlify

def aes_decrypt(ciphertext, key):
    # Decode the hex encoded ciphertext and key
    ciphertext = unhexlify(ciphertext)
    key = unhexlify(key)

    # Ensure the key length is valid (16 bytes for AES-128, 24 bytes for AES-192, 32 bytes for AES-256)
    assert len(key) in [16, 24, 32]

    cipher = AES.new(key, AES.MODE_ECB)
    plaintext = cipher.decrypt(ciphertext)

    return hexlify(plaintext).decode()

# Test the function
key = "1A  6C  FA  38  01  64  EF  A1  42  15  A4  54  89  22  86  FF".replace(" ", "")
log = """
2023-06-23 01:22:25,060 # 00000000  EE  AE  C7  EA  8D  10  67  9D  2C  43  D5  B2  19  66  0D  00
2023-06-23 01:22:25,062 # 00000010  AF  5E  E3  B3  1C  9A  4B  C3  D4  DE  D6  1A  58  E8  A1  79
2023-06-23 01:22:25,063 # 00000020  42  DD  96  76  A7  CA  5F  3F  63  BB  C4  7D  86  7D  6B  44
2023-06-23 01:22:25,064 # 00000030  07  D9  C2  B1  8D  D6  97  10  85  A0  C5  99  19  1B  52  01
2023-06-23 01:22:25,065 # 00000040  86  09  95  4B  4B  14  FA  C9  62  9E  44  81  DE  D6  40  EF
2023-06-23 01:22:25,067 # 00000050  66  BF  E3  9E  26  AA  DD  32  1A  E4  8F  17  87  2F  70  F5
2023-06-23 01:22:25,068 # 00000060  79  F1  3E  98  1B  20  66  ED  BB  63  6F  3B  C9  B4  F7  06
2023-06-23 01:22:25,069 # 00000070  D8  21  0D  B1  7A  EC  32  A8  5C  4B  C4  D7  B9  C6  D3  2C
"""

# Split log into lines
lines = log.split("\n")

# Extract hex numbers
hex_nums = [line.split("#")[1].split()[1:] for line in lines if line.strip()]

# Join hex numbers into a single string
hex_string = ''.join([''.join(nums) for nums in hex_nums])

print(hex_string)

print(key)
print(aes_decrypt(hex_string, key))
