import secrets
import binascii

# This generates a random AES-128 key.
key = secrets.token_bytes(16) 

# Convert key into hexadecimal
hex_key = binascii.hexlify(key).decode()

# Write the key to a file
with open("key.hex", "w") as key_file:
    key_file.write(hex_key)

print(f"AES-128 key has been generated and saved to key.hex")

