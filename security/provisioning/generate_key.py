from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes

# Function to generate a random AES-128 key
def generate_key():
    key = get_random_bytes(16)  # AES-128 key size is 16 bytes
    return key.hex()  # Convert key to hexadecimal format

# Function to write the key to a file
def write_key_to_file(key):
    with open("key.hex", "w") as key_file:
        key_file.write(key)

# Generate the key and write it to a file
key = generate_key()
write_key_to_file(key)

