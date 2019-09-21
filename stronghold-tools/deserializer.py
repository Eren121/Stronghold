from struct import *
from Filetimes import *
import zlib

offset = 0
file_content = b''

def get_offset():
    global offset
    return offset

def read_compressed_file_content(file_name):
    global offset
    global file_content
    map_file = open(file_name, 'rb')
    file_content = map_file.read()
    file_content = zlib.decompress(file_content)
    offset = 0

def read_file_content(file_name):
    global offset
    global file_content
    map_file = open(file_name, 'rb')
    file_content = map_file.read()
    offset = 0

def separator():
    print('---------------------------')

def bytes_to_str(bytes):
    return bytes.decode("utf-8")

def unpack_next(format):
    global file_content
    global offset
    ret, = unpack_from(format, file_content, offset)
    offset += calcsize(format)
    return ret

def next_bytes(count):
    return unpack_next(str(count) + 's')

def next_int8():
    return unpack_next('b')

def next_int32():
    return unpack_next('i')

def next_int64():
    return unpack_next('q')

def next_float():
    return unpack_next('f')

def next_string():
    length = next_int32()
    return bytes_to_str(next_bytes(length))

def next_widestring():
    length = next_int32()
    characters = next_bytes(length * 2)
    return bytes_to_str(characters[::2])

def next_filetime():
    return filetime_to_dt(next_int64())

skip_next_bytes = next_bytes
