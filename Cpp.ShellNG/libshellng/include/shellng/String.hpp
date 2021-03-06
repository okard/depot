/*
Copyright (c) 2013 okard

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in 
the Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies 
of the Software, and to permit persons to whom the Software is furnished to do 
so, subject to the following conditions: The above copyright notice and this 
permission notice shall be included in all copies or substantial portions of 
the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
SOFTWARE.
*/
#pragma once
#ifndef __SHELLNG_STRING__
#define __SHELLNG_STRING__

#include <shellng/Buffer.hpp>

namespace sng {
	
/**
* Internal String Representation
*/
class String : public Buffer
{
private:
	Encoding encoding_;

	
public:

	String();
	String(const String& str);
	String(const char* str);
	
	virtual ~String();
	
	
	String& operator=(const String& str);
	String& operator=(const char* str);
	
	bool operator==(const String& str);
	bool operator==(const char* str);
	
	//convert between formats
	//
	
	//compare Const char* 
	//make sure last byte is a \0
	
};
	
} //end namespace sng

#endif
