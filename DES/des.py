""" This is a DES implementation by Joshua Pepple """

# this handles encoding and decoding of string bytes to aid returning to characters without writing a hex to string decoder myself
import base64

# key permutation lists
p = [16, 7, 20, 21,
     29, 12, 28, 17,
     1, 15, 23, 26,
     5, 18, 31, 10,
     2, 8, 24, 14,
     32, 27, 3, 9,
     19, 13, 30, 6,
     22, 11, 4, 25]

ip = [58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
      62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
      57, 49, 41, 33, 25,  17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
      61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7]

ip_inv = [40, 8, 48, 16, 56, 24, 64, 32,
          39, 7, 47, 15, 55, 23, 63, 31,
          38, 6, 46, 14, 54, 22, 62, 30,
          37, 5, 45, 13, 53, 21, 61, 29,
          36, 4, 44, 12, 52, 20, 60, 28,
          35, 3, 43, 11, 51, 19, 59, 27,
          34, 2, 42, 10, 50, 18, 58, 26,
          33, 1, 41, 9, 49, 17,57, 25]

e_table = [32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9,
           8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
           16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
           24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1]

pc_1 = [57, 49, 41, 33, 25, 17, 9,1, 58, 50, 42, 34, 26, 18,
        10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36,
        \
        63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22,
        14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4]

pc_2 = [14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10, 23, 19, 12, 4,
        26, 8, 16, 7, 27, 20, 13, 2, 41, 52, 31, 37, 47, 55, 30, 40,
        51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32]

left_shift_scheme = {1: 1, 2: 1, 3: 2, 4: 2, 5: 2, 6: 2, 7: 2, 8: 2, 9: 1, 10: 2, 11: 2, 12: 2, 13: 2, 14: 2, 15: 2, 16: 1}

# s-boxes
s1 = [[14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7],
      [0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8],
      [4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0],
      [15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13]]

s2 = [[15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10],
      [3, 13, 4, 7 ,15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5],
      [0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15],
      [13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9]]

s3 = [[10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8],
      [13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1],
      [13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7],
      [1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12]]

s4 = [[7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15],
      [13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9],
      [10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4],
      [3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14]]

s5 = [[2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9],
      [14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6],
      [4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14],
      [11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3]]

s6 = [[12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11],
      [10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8],
      [9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6],
      [4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13]]

s7 = [[4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1],
      [13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6],
      [1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2],
      [6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12]]

s8 = [[13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7],
      [1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2],
      [7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8],
      [2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11]]

s_boxes = {1: s1, 2: s2, 3: s3, 4: s4, 5: s5, 6: s6, 7: s7, 8: s8}

def getBinary(string):
    """ This takes a string and returns the binary equivalent """
    hex_str = base64.b16encode(bytes(string, 'utf-8')).decode()
    bin_str = bin(int(hex_str, base=16))[2:]

    if len(bin_str) < 4 * len(hex_str):
        diff = (4 * len(hex_str)) - len(bin_str)
        bin_str = ('0'*diff) + bin_str
    return bin_str

def permute(choice, key):
    """ This takes a permutation choice list and a key and returns a new permuted key. """
    new_key = ''
    for i in choice:
        new_key += key[i-1]
    return new_key

def left_shift(bin, offset):
    """ This performs a left bitwise shift on a string representation of a binary number. """
    return bin[0+offset:]+bin[0: offset]

def keygen(key_bin):
    """ This handles all round key generation implementations. """
    init_perm_key = permute(pc_1, key_bin)
    c = init_perm_key[0:28]
    d = init_perm_key[28:]

    # store initial round key and then compute other round keys
    pre_keys = []
    i = 0
    while i <= 15:
        c = left_shift(c, left_shift_scheme[i+1])
        d = left_shift(d, left_shift_scheme[i+1])
        pre_keys.append((c, d))
        i += 1

    # generate round keys
    _keys = []
    for k, v in pre_keys:
        _keys.append(permute(pc_2, k + v))
    return _keys

def fiestel(text_bin, keys, depth=0):
    """ This implements the 16 rounds using the keys """
    if (depth == 16):
        l = text_bin[0:32]
        r = text_bin[32:]
        return permute(ip_inv, r+l)

    if depth == 0:
        text_ip = permute(ip, text_bin)
    else:
        text_ip = text_bin

    l0 = text_ip[0:32]
    r0 = text_ip[32:]
    
    li = r0
    # expand r0 from 32 bits to 48 bits
    r0 = permute(e_table, r0) 
    #perform initial xor with first key
    ri = xor(r0, keys[0])
    
    # split 48 bits into 8 groups of 8 bits
    s_box_output = ''
    i = 0
    count = 0
    while True:
        portion = ri[i:i+6]
        i += 6
        count += 1
        if count > 8:
            break
        s_box_output += perform_sbox(portion, count)
    f = permute(p, s_box_output)
    ri = xor(l0, f)
    return fiestel(li+ri, keys[1:], depth+1)
    

def perform_sbox(portion, s_box_number):
    """ This takes a binary portion and the s-box number and returns the binary form of the 4 bit s box """
    sbox = s_boxes[s_box_number]
    row = int(portion[0]+portion[5],2)
    col = int(portion[1:5],2)
    sub = bin(sbox[row][col])[2:]
    if len(sub) < 4:
        sub = ('0' * (4 - len(sub))) + sub
    return sub

def xor(bin_a, bin_b):
    """ This takes 2 binary strings and returns their binary XOR result """
    a = int(bin_a, 2)
    b = int(bin_b, 2)
    c = bin(a ^ b)[2:]
    c = ('0'* (len(bin_a) - len(c))) + c
    return c

def getHex(bin):
    """ This returns the hex format of a binary string """
    return hex(int(bin, 2))[2:]

def decrypt(hex, keys):
    """ This decrypts an hex cipher string back to the original message using the keys """
    binary = bin(int(hex, 16))[2:]

    if len(binary) < (len(hex) * 4):
        binary = ('0'* (4*len(hex) - len(binary))) + binary

    i = 0
    plain = ''
    while True:
            if len(binary[i:]) > 64:
                block = binary[i:i+64]
                i += 64
                plain += fiestel(block, keys)
            else:
                diff = 64 - len(binary[i:])
                block = binary[i:] + (('0')*diff)
                plain += fiestel(block, keys)
                break

    plain = base64.b16decode(bytes(getHex(plain).upper(), 'utf-8')).decode()
    return plain

def _main():
    """ This is the  main function """
    
    ch = input('(e)ncrypt or (d)ecrpyt [e\d]- ')

    if ch == 'e':
        file = input('Enter filename: ')
        
        key = input('Enter 16 digit hex key: ')

        # open and read file strings and convert to hex form
        with open(file) as f:
            fileContents = f.read()

        # convert message and key into binary
        plain_bin = getBinary(fileContents)
        key_bin = bin(int(key, 16))[2:]

        if len(key_bin) < 64:
            key_bin = ('0' * (64 - len(key_bin))) + key_bin

        # generate round keys
        round_keys = keygen(key_bin)

        i = 0
        cipher = ''
        while True:
            if len(plain_bin[i:]) > 64:
                block = plain_bin[i:i+64]
                i += 64
                cipher += fiestel(block, round_keys)
            else:
                diff = 64 - len(plain_bin[i:])
                block = plain_bin[i:] + (('0')*diff)
                cipher += fiestel(block, round_keys)
                break
        
        cipher = hex(int(cipher, 2))[2:]
        round_keys.reverse()
        print('CIPHER => ', cipher, sep='\n')
        
        save = input('Save cipher to file? [y/n] - ')
        if save == 'y':
            file = input('Enter filename: ')

            with open(file, 'a+') as f:
                f.write(cipher)
                print('file write complete')
        
    elif ch == 'd':
        file = input('Enter filename: ')
        # remember to change key to hex implementation
        key = input('Enter 16 digit hex key: ')

        # open and read file strings and convert to hex form
        with open(file) as f:
            fileContents = f.read()
        
        key_bin = bin(int(key, 16))[2:]
        if len(key_bin) < 64:
            key_bin = ('0' * (64 - len(key_bin))) + key_bin

        # generate round keys
        round_keys = keygen(key_bin)
        d_keys = round_keys[:]
        d_keys.reverse()
        plaintext = decrypt(fileContents, d_keys)
        print('PLAINTEXT => \n', plaintext, sep='')

_main()

# 0123456789abcdef