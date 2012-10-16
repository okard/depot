

%include {
#include <cstdio>
#include <cassert> /* required for building */
#include <shellng/Token.hpp>
#include <shellng/Ast.hpp>
#include "ParseContext.hpp"
using namespace sng;
}

// also can make callbacks to notifier about parsing states
%extra_argument { ParseContext *ctx }


%token_prefix {TOKEN_}

%token_type { Token* }

//%token_destructor {delete $$;}


//define the types for all non terminals
%type program { Node* }
//%destructor 

/*
* Parser Accepts
*/

%parse_accept {
    ctx->errStream << "Parsing Complete" << std::endl;
}

/*
 Error Handling Section
*/

%syntax_error {
    //call error on extra argument
    // ctx->syntaxError
    // which prints line and so on
    ctx->error = true;
    ctx->errStream << "Syntax error" << std::endl;
    //fprintf(stderr, "Syntax error\n");
}

%parse_failure {
    //same here
    ctx->error = true;
    ctx->errStream << "Giving up. Parser is hopelessly lost..." << std::endl;
    //fprintf(stderr,"Giving up. Parser is hopelessly lost...\n");
}

//%stack_overflow 

/*
* Syntax Starts here
*/

%start_symbol program

program ::= INTEGER(a). {
    a->integer=0;
    ctx->ast = new Node();
}

program ::= KW_DEF IDENTIFIER. {
    ctx->ast = new Node();
}

/*
program ::= def
program ::= com

com ::= 

com ::= IDENTIFIER ARGS
*/
