/*
    Universal Typesetting System - Core
    
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
    
    Units
*/
#ifndef __UTSC_UNITS_H__
#define __UTSC_UNITS_H__

/**
* Unit Type
*/
typedef enum uts_unit_type
{
    UTS_UNIT_DTPPOINT,
    UTS_UNIT_CM,
    UTS_UNIT_MM,
    UTS_UNIT_INCH,
    UTS_UNIT_PERCENT
    
} uts_unit_type;


/**
* Unit Structure
*/
typedef struct uts_unit
{
    ///unit type
    uts_unit_type type;
    /// unit value
    float value;
    
} uts_unit;



#endif /* __UTSC_UNITS_H__ */