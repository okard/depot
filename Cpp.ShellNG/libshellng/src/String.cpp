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

#include <shellng/String.hpp>

#include <string>

using namespace sng;


String::String()
	: encoding_(ENCODING_UTF8)
{
}

String::String(const String& str)
{
	//str.copyTo(*this, 0, str.size());
}

String::String(const char* str)
{
	auto size = std::char_traits<char>::length(str);
	char* sstr = const_cast<char*>(str);
	write(reinterpret_cast<ubyte8*>(sstr), size);
}

String::~String()
{
}

String& String::operator=(const String& str)
{
	 if (this != &str) 
	 {
	 }
	 return *this;
}

String& String::operator=(const char* str)
{
	
	return *this;
}

bool String::operator==(const String& str)
{
	return false;
}

bool String::operator==(const char* str)
{
	return false;
}
	
