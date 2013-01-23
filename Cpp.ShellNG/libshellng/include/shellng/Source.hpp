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
#pragma once
#ifndef __SHELLNG_SOURCE__
#define __SHELLNG_SOURCE__

#include <cstdio>

#include <shellng/Buffer.hpp>
#include <shellng/Types.hpp>

namespace sng {
 
//Location    

/**
* Interface for Source Files
* Can be used for callback source (via stdin)
* Or for files
*/
class Source
{   
public:
    virtual ~Source(){};
    
    /**
    * return a buffer with data len
    * size depends on implementation
    * buffer has to be freed after usage
    */
    virtual void* read(size_t* len)=0;
    
    //free buffers via source?
    //virtual void free(void* buffer)=0;
    
    /**
    * Read a specific amount to buffer
    * maximum len but can be less
    */
    virtual size_t read(void* buffer, size_t len)=0;
    
    /**
    * No more data available
    */
    virtual bool isEOF()=0;
    
    /**
    * Encoding 
    */
    virtual Encoding getEncoding() = 0;
};


/**
* Source File
* to read from a file
*/
class SourceFile : public Source
{
private:
    FILE* file_;
    
public:
    /**
    * Create a new instance of a SourceFile
    */
    SourceFile();
    
    /**
    * Destroy SourceFile object
    */
    virtual ~SourceFile();
    
    /**
    * Open a file for reading
    */
    void open(const char* fileName);
    
    /**
    *
    */
    virtual void* read(size_t* len);
    
    /**
    * Read from file into buffer
    */
    virtual size_t read(void* buffer, size_t len); 
    
    /**
    * Position is at end of file
    */
    virtual bool isEOF();
    
    /**
    * Encoding
    */ 
    virtual Encoding getEncoding();
};
    
    
}


#endif
