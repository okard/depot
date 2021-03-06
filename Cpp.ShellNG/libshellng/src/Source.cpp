/*
Copyright (c) 2012 okard

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

#include <shellng/Source.hpp>

#include <cstdlib>

#include <shellng/Exception.hpp>

using namespace sng;


/**
* Create a new instance of a SourceFile
*/
SourceFile::SourceFile()
    : file_(NULL)
{
}

/**
* Destroy SourceFile object
*/
SourceFile::~SourceFile()
{
    if(file_ != NULL)
        fclose(file_);
}

/**
* Open a file for reading
*/
void SourceFile::open(const char* fileName)
{
    if(file_ != NULL)
        fclose(file_);
    
    file_ = fopen(fileName, "r");
    
    
	if(file_ == NULL)
		throw Exception("Can't open file");
}

/**
* Read try to read specific length
* returns buffer
* requires free after usage
*/
void* SourceFile::read(size_t* len)
{
    void* buffer = malloc(1024);
    
    *len = fread(buffer, 1, 1024, file_);
    
    return buffer;
}

/**
* Read from file into buffer
*/
size_t SourceFile::read(void* buffer, size_t len)
{
    return fread(buffer, 1, len, file_);
}

/**
* Position is at end of file
*/
bool SourceFile::isEOF() const
{
    return feof(file_);
}


Encoding SourceFile::getEncoding() const
{
	//default UTF8
	//check bom etc
	return ENCODING_UTF8;
}

//for reset  rewind (file_);
