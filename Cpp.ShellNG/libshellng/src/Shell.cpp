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

#include <iostream>
#include <cstdlib>

#include <uv.h>

#include <shellng/Shell.hpp>
#include <shellng/Lexer.hpp>


#include "ParseContext.hpp"

using namespace sng;


// uv_loop_t *loop = uv_loop_new();
// uv_loop_t *loop = uv_default_loop();
// uv_work_t req;
// uv_queue_work(loop, &req, fib, after_fib);
// req.data = (void*)bla;



Shell::Shell()
{
    
    //register default objects to rootContext
    
    //$env, 
    //$sys
}

Shell::~Shell()
{
}


const char* Shell::getPrompt() const
{
    //execute or get it depends of ast type
    
    //if ($sys.prompt.type == function, interpreter run()
    //if ($sys.prompt.type == string -> print
    
    //still returns string?
    
    // $sys.prompt
    
    //execute underlying ast
    
    return "shellng > ";
}


void Shell::execute(const std::shared_ptr<Source>& src)
{
	//open source file
	parser_.getLexer().open(src);
    
    NodePtr ast = parser_.parse();
    
    
    //Interpreter.execute()
    
}



void Shell::dispatch()
{
    //run event loop
    
    //
    //uv_run_once(uv_loop_t*);
    
}
