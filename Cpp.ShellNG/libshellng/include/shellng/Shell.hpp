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
#ifndef __SHELLNG_SHELL__
#define __SHELLNG_SHELL__

#include "Lexer.hpp"
#include "Context.hpp"
#include "Source.hpp"


namespace sng {

/**
* Next generation shell
*/
class Shell
{
private:
    //Lexer
    Lexer lexer_;
    
    //encapsulate in own class?
    //Lemon parser
    void* parser_;
    
    //prompt is a function call?
    
    
    //currentContext
    //rootContext
    
    //function pointer void RequestInput(Shell& shell)

    typedef void(*RequestInputFunc)(Shell& shell);

public:
    Shell();
    ~Shell();

    const char* getPrompt() const;
    
    /**
    * Execute a source
    * return bool?
    */
    void execute(Source* const src);
    
private:  
    void parse(char* line);
    
    //ExecuteFile(const char* fileName);

};

}

#endif // __SHELLNG_SHELL__