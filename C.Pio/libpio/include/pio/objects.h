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
    
    PIO Types
*/
#ifndef __LIBPIO_OBJECTS_H__
#define __LIBPIO_OBJECTS_H__

#include <cpr/types.h>

//sha256 32byte id
typedef unsigned char pioid[32];


/**
* Properties of piobjects
* Properties are safed in MessagePack Format
* Properties Ids are RawByte
* Format: 0xa1-id--data
*/
typedef enum pio_property
{
    pio_property_title = 0x01, //title string variable length (utf8)
    pio_property_author = 0x02, //string
    
    pio_property_tag = 0x04, //a linked tag pioid 32 byte
    
    pio_property_data_chunk = 0xFE, //chunk data when object is bigger as 4 GB
    pio_property_data = 0xFF //the object data 0xdf-size-data
    
} pio_property;


/**
* piobject types
*/
typedef enum pio_type
{
    pio_type_txt = 0x01,  //Text
    pio_type_md = 0x02,   //Markdown
    pio_type_html = 0x03, //XHTML
    pio_type_link = 0x04, //Links
    pio_type_img = 0x05,  //Whiteboard Image
    
    //calendar
    //task list
    
    
    pio_type_tag = 0xB0, //Tag - String
    pio_type_res = 0xB1, //Resource - FileName - Data
    pio_type_ref = 0xB2, //References/Linked PIOs
    
    
    pio_type_tree = 0xA0 //Tree
     
    
} pio_type;


/**
* piobject header
*/
typedef struct pio_header
{
    ushort version;
    ubyte encrypted;    //default:aes
    ubyte compressed;   //default: lzma
    pio_type type;
    
    //count of properties?
    
} pio_header;


/**
* Personal information object
*/
typedef struct piobj
{
    pioid id;
    pio_header header;
    
    //object data
    //object properties -> list? -> hashtable?
    
} piobj;




#endif