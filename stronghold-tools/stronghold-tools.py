from deserializer import *

read_file_content('C:\Program Files (x86)\Firefly\Stronghold 2\maps\Australia.s2m')
separator()

nb_widestring_options = next_int32()

for i in range(nb_widestring_options):
    option_key = next_string()
    option_value = next_widestring()

    print('Option widestring #' + str(i + 1) + ':')
    print('\tkey:', option_key)
    print('\tvalue:', option_value)

separator()

nb_integer_options = next_int32()

for i in range(nb_integer_options):
    option_key = next_string()
    option_value = next_int32()

    print('Option integer #' + str(i + 1) + ':')
    print('\tkey:', option_key)
    print('\tvalue:', option_value)



#  lastdate:
# 23 DA 00 00:  28/08/2019 23:18:24
# 24 DA 00 00:  20/09/2019 01:00:52
# 25 DA 00 00:  20/09/2019 01:01:56
# 00 00 00 00:
#
#


separator()
