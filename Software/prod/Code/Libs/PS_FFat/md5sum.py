#!/usr/bin/python3
import hashlib

with open("testFile_shortest.txt", "r") as f:  
    list_text = f.readlines()

for i in range(len(list_text)):
    list_text[i] = list_text[i].decode('utf-8')

test_file_text = ''
test_file_text = test_file_text.join(list_text);

print(test_file_text) #.decode('utf-8'))

hash_object = hashlib.md5(test_file_text.encode())
md5_hash = hash_object.hexdigest()

print(md5_hash)
