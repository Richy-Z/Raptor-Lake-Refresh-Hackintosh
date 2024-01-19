import binascii

with open("iMacPro1,1 = Mac-7BA5B2D9E42DDD94.plist", "r", encoding="utf-8") as i:
    global input
    input = i.read()
    i.close()

def binary_to_hex(bin_data):
    return binascii.hexlify(bin_data)

def utf8_to_binary(utf_data):
    return utf_data.encode()

input = utf8_to_binary(input)
input = binary_to_hex(input)

with open("output.hex.txt", "wb") as out:
    out.write(input)
    out.close()
