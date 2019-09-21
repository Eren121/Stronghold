import zlib
import struct
import sys
import os
from deserializer import *

file_name = 'C:/Users/Raphael/Documents/Stronghold 2/config.dat'

if len(sys.argv) == 3:
    if sys.argv[1] == '-d':
        file_content = open(file_name, 'rb')
        file_content = file_content.read()
        file_content = zlib.decompress(file_content)
        out_file = open(sys.argv[2], 'wb')
        out_file.write(file_content)
    elif sys.argv[1] == '-c':
        file_content = open(sys.argv[2], 'rb')
        file_content = file_content.read()
        file_content = zlib.compress(file_content)
        out_file = open(file_name, 'wb')
        out_file.write(file_content)
    exit();

read_compressed_file_content(file_name)
skip_next_bytes(0x2A)

print('Pseudo:', next_widestring())

# Volumes are normalized floats between [0;1]. The displayed value is
# volume * 128

music_volum = next_float() * 128
print('Music volum:', music_volum)

voice_volum = next_float() * 128
print('Voice volum:', voice_volum)

sound_volum = next_float() * 128
print('Sound volum:', sound_volum)

skip_next_bytes(0x19)

game_speed = next_int32()
print('Game speed:', game_speed)

# Campaign unlock

for i in range(12):
    campaign_unlocked = next_int8()
    print('Campaign #' + str(i) + ' unlocked:', campaign_unlocked)

# 0x00 => First siege
# 0x01 => Second siege
# ...
# Ox0A => Last siege
# 0x0B => Victory screen

conquest_trail = next_in32()
print('Conquest trail:', conquest_trail)
