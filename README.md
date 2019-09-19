
# Stronghold Tools

## Binary Format

### Introduction

To decipher the format, we need to figure out what each data segment represents. We also need a common template notation that represents the data that can convert real file binary code into information and vice-versa.

A file represents contiguous data which is composed of bytes. Each byte is representable into a hexadecimal number of 2 digits. It's how hexadecimal editors work.

Since we can't read binary text and editors don't represent it correctly, we need to use a conversion to decipher it. 

The file look like this:

`6d 79 20 64 61 74 61` (represents the string `my data` in hexadecimal)

### Structures

It's not difficult to assume that tha data has **repetitive patterns** and each time a chunk of data need to be saved, it's saved the same way. We can figure out which are the most common structures and the more structures we have, the more we can interpret the file. A structure behiave exactly like a serializable *Class*, or *primitive* in **Java** or **C++**. The most common structures are **strings** and **integers**.

## Primitives

The primitives are the most basic structures of the file and are everywhere. **Firefly** use *Little-Endian* for saving its files and the integers are stored on *32 bits*.

**Notation**: The notation **look like** [Google's Protocol Buffers](wikipedia.org/wiki/Protocol_Buffers) notation, since it is convenient to use that way.
**Endianess**: *Little-Endian*

### Chars

A **char** (or a **byte** or an **int8** is just a 8-bits chars), between *0* and *255*.

```protobuf
message byte { /* or char or int8 */
	/* one byte */
}
```

### Integers

The most basic one, an integer is just.. A (32 bits) integer.

```protobuf
message int32 { // Same as Google's native int32 type
	/* 4  bytes */
}
```

**Example:** The data `255` is serialized into `ff 00 00 00` *(little endian)*

We also here implictly define unsigned and signed 1, 2, 4 and 8 bytes-sized integers.

### Lists

Repetitive data is named as a **List**.
A **List** contains a **size** and repeatitively **size**-time a chunk of arbitrary data.
The size is stored in front of the List. It has a **int32** type.
We can use the Google's protobuf `repeat` notation for that.

### Strings

Since we have defined the **Lists**, a string is no more than a list of characters.
```protobuf
message string {
	repeated int8 characters = 1;
}
```

### Wide Strings

There is some strings that are more complicated in map files. These strings take 2 times more space than usual strings because each char take 2 bytes. However, the second byte is always zero. It's maybe because in region languages, the second byte is used.

```protobuf
message widestring {
	repeated int16 characters = 1;
}
```

## Map format

```protobuf
message S2M_Format {
	Header header = 1;
	compressed Segment1 = 2; // We will use the keyword "compressed" to define some compressed data
	compressed Segment2 segment2 = 3; // zlib, default compression
	compressed Segment3 segment3 = 4;
}
```

## Header

```protobuf
message Header {
	message OptionInteger {
		string key = 1;
		int32 value = 2;
	}
	message OptionWidestring {
		string key = 1;
		widestring value = 2;
	}
	
	repeated OptionWidestring options_str = 1;
	repeated OptionInteger options_int = 2;
}
```

Contains some general options.
