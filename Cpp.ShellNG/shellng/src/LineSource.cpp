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

#include <cstdlib>
#include <cstring>

extern "C" 
{
    #include <linenoise.h>
}

#include "LineSource.hpp"

using namespace sng;


LineSource::LineSource(const Shell& shell)
    : shell_(shell), eof_(false)
{
}
    
LineSource::~LineSource()
{
}

void* LineSource::read(size_t* len)
{
    if(eof_)
    {
        *len=0;
        return nullptr;
    }
    
    //first use internal buffer
    
    char* line = linenoise(shell_.getPrompt());
    if(line == NULL 
    || line[0] == '\0')
    {
        *len = 0;
        eof_=true;
        return nullptr;
    }
    
    eof_=true;
    *len = strlen(line);
    linenoiseHistoryAdd(line);
    return line;
}


size_t LineSource::read(void* buffer, size_t len)
{
    if(eof_)
        return 0;
    
    //first use internal buffer
    
    //full prompt or half prompt
    //shell.rootContext["sys"]["prompt"].toString()
    
    char* line = linenoise(shell_.getPrompt());
    
    if(line == NULL || line[0] == '\0')
    {
        eof_=true;
        return 0;
    }
    
    auto inLen = strlen(line);
    
    //copy to buffer
    if(inLen <= len)
    {
        strncpy (static_cast<char*>(buffer), line, inLen);
        free(line);
        return inLen;
    }
    else
    {
        throw "fail";
        //copy len to buffer
        //safe rest in internal buffer
    }
    
    return 0;
}
    
    
bool LineSource::isEOF()
{
    return eof_;
}

Encoding LineSource::getEncoding()
{
	 //look into LANG Enviroment Variable?
	 return ENCODING_UTF8;
}


void LineSource::reset()
{
    eof_=false;
}
