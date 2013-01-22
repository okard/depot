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


//TODO include in Namespace?
namespace Parser {
#include "Parser.c"
}

using namespace sng;


// uv_loop_t *loop = uv_loop_new();
// uv_loop_t *loop = uv_default_loop();
// uv_work_t req;
// uv_queue_work(loop, &req, fib, after_fib);
// req.data = (void*)bla;



Shell::Shell()
{
    this->parser_ = Parser::ParseAlloc(malloc);
    
    
    //register default objects to rootContext
    
    //$env, 
    //$sys
}

Shell::~Shell()
{
    Parser::ParseFree(this->parser_, free);
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


void Shell::execute(Source* const src)
{
    //open source file
    lexer_.open(src);
    
    //creates a parsing context used as proxy between shell and parser
    ParseContext ctx(*this);
    
    //create new token for every step and let lemon clena them up
    Token tok;
    
    //ParseTrace(stderr, (char*)"[Parser] >> ");
    
    while(unsigned int tokId = lexer_.next(tok))
    {
        //filter for first 0 token?
        
        std::cout << "Token: " << tokId << std::endl;
        Parser::Parse(this->parser_, tokId, &tok, &ctx); 
        
        //if(ctx.error)
            
    }
    Parser::Parse(this->parser_, 0, &tok, &ctx);
    
    if(ctx.ast != nullptr)
    {
        std::cout << "Interpret" << std::endl;
        //interpreter->interpret()
    }
    
    
    /*
    while(ctx.ast == nullptr)
    {
        Token tok;
        
        std::cout << "Lexer call" << std::endl;
        unsigned int tokId = lexer_.next(tok);
        std::cout << "Token: " << tokId << std::endl;
        
        if(tokId == 0)
        {
            //invalid token
        }
        
        //bind current context
        ::Parse(this->parser_, tokId, &tok, &ctx);
        
        std::cout << "AST: " << ctx.ast << std::endl;
       
        //parse 0 in the right moment to geht ide
        //make source 
       
        if(ctx.error)
            break;
    }*/
}



void Shell::dispatch()
{
    //run event loop
    
    //
    //uv_run_once(uv_loop_t*);
}
