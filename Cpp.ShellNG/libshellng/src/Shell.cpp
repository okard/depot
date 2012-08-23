
#include <shellng/Shell.hpp>
#include <shellng/Lexer.hpp>

#include <cstdlib>
#include "Parser.c"


using namespace sng;


// uv_loop_t *loop = uv_loop_new();

Shell::Shell()
{
    this->parser_ = ::ParseAlloc(malloc);
    
}

Shell::~Shell()
{
    
}


const char* Shell::getPrompt()
{
    return "shellng > ";
}


void Shell::parse(char* line)
{
    //add to internal buffer
    Token tok;
    unsigned int tokId = lexer_.next(tok);
    
    if(tokId == 0)
    {
        //invalid token
    }
    
    ::Parse(this->parser_, tokId, &tok);
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
