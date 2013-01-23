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

#include "Source.hpp"
#include "Parser.hpp"

#include "Context.hpp"

namespace sng {

/**
* Next generation shell
*/
class Shell
{
private:
	//parser
    Parser parser_;
    
    
    //event loop und jobs
        //parse -> job -> enter eventloop
        //Stdin is also an special job from libuv
        //see also Shell::dispatch
    
    
    //Root Context with Global Objects
    Context rootContext;
    
    //currentContext
    //rootContext

public:
    Shell();
    ~Shell();

    const char* getPrompt() const;
    
    /**
    * Execute a source
    * return bool?
    * enqueue?
    */
    void execute(Source* const src);
    
    //execute in seperate context for example sandboxed scripts
    //void execute(Source* const src, Context* const ctx);
    
    //rename execute to enqueue?
    //add a special prefined JobClass to do that?
    //user worker threads to pull from queue
    
    
    /**
    * On tick for event loop
    * return true or false?
    */
    void dispatch();
    
    //void run();
    
    
private:  
    
    //ExecuteFile(const char* fileName);

};

}

#endif // __SHELLNG_SHELL__
