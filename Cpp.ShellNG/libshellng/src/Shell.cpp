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

#include <shellng/Shell.hpp>
#include <shellng/Lexer.hpp>

#include <iostream>

#include <cstdlib>

#include "ParseContext.hpp"
#include "Parser.c"

using namespace sng;


// uv_loop_t *loop = uv_loop_new();

Shell::Shell()
{
    this->parser_ = ::ParseAlloc(malloc);
    
}

Shell::~Shell()
{
    ParseFree(this->parser_, free);
}


const char* Shell::getPrompt() const
{
    return "shellng > ";
}


void Shell::execute(Source* const src)
{
    lexer_.open(src);
    
    ParseContext ctx(*this);
    
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
    }
    
    
    //interpreter->interpret(context.node, context)
}


/*

YYSTYPE yylval;
Scanner scanner(&std::cin);
    void *pParser = ParseAlloc(malloc);
    int tokenID;

#if 0
ParseTrace(stderr, (char*)"[Parser] >> ");
#endif

    ParserState state;
    // scanner.scan return 0 when get EOF.
    while (tokenID = scanner.scan(yylval)) 
    
    {
        // printf("GET TOKEN: %d\n", tokenID);
        Parse(pParser, tokenID, yylval, &state);
    }
    Parse(pParser, 0, yylval, &state);
    ParseFree(pParser, free);

*/
