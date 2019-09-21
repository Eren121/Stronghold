from deserializer import *

# for each map map name then dummy data
# In order, for a given sh2.cache:
# 73 C6 F1 25 47 6F D5 01           (8 bytes)
# 01 00 00 00 41 01 00              (7 bytes)
# F4 37 BD 69 9B 5D D5 01
# 79 86 0A 00 41 01 00
# E2 41 FE 6E E0 5D D5 01
# 23 DA 00 00 41 01 00
#
#
# Look like one time one in two, the dummy data segment
# is length of 7 bytes and one time in two, 8 bytes,
# with the first given at 8 bytes.

read_file_content('C:/Users/Raphael/Documents/Stronghold 2/Maps/sh2.cache')

skip_next_bytes(16)

print(next_string())

for i in range(4):
    print('Option #' + chr(ord('a') + i) + ':', next_int32())

nb_cached_files = 20
for i in range(nb_cached_files):
    print(next_widestring())
    skip_next_bytes(7 + (i + 1) % 2)


print('Final offset:', get_offset())
