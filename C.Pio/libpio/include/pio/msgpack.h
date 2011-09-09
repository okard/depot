/*
    Personal Information Objects
    
    Copyright (c) 2011  okard

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
    
    Message Pack Types
*/
#ifndef __LIBPIO_MSGPACK_H__
#define __LIBPIO_MSGPACK_H__


/**
* Message Pack Types
* see http://wiki.msgpack.org/display/MSGPACK/Format+specification
*/
typedef enum msgpack_type
{
    // Full Byte IDs
    msgpack_type_nil = 0xc0,
    msgpack_type_false = 0xc2,
    msgpack_type_true = 0xc3,
    msgpack_type_float = 0xca,
    msgpack_type_double = 0xcb,
    msgpack_type_uint8 = 0xcc,
    msgpack_type_uint16 = 0xcd,
    msgpack_type_uint32 = 0xce,
    msgpack_type_uint64 = 0xcf,
    msgpack_type_int8 = 0xd0,
    msgpack_type_int16 = 0xd1,
    msgpack_type_int32 = 0xd2,
    msgpack_type_int64 = 0xd3,
    msgpack_type_raw16 = 0xda,
    msgpack_type_raw32 = 0xdb,
    msgpack_type_array16 = 0xdc,
    msgpack_type_array32 = 0xdd,
    msgpack_type_map16 = 0xde,
    msgpack_type_map32 = 0xdf,
    
    //Fixed -> value & ~mask == type
    msgpack_type_pfixnum = 0x00,
    msgpack_type_pfixnum_mask = 0x7f, 
    msgpack_type_fixmap = 0x80,
    msgpack_type_fixmap_mask = 0x8f,
    msgpack_type_fixarray = 0x90, 
    msgpack_type_fixarray_mask = 0x9f,
    msgpack_type_fixraw = 0xa0, 
    msgpack_type_fixraw_mask = 0xbf,
    msgpack_type_nfixnum = 0xe0, 
    msgpack_type_nfixnum = 0xff 
    
    
} msgpack_type;


#endif
