

%include {
#include <cstdio>
#include <cassert> /* required for building */
#include <shellng/Token.hpp>
#include <shellng/Ast.hpp>
#include "ParseContext.hpp"
using namespace sng;
}

%token_prefix {TOKEN_}

%token_type { Token* }

// also can make callbacks to notifier about parsing states
%extra_argument { ParseContext *ctx }

%type program { Node* }

%syntax_error {
    //call error on extra argument
    // ctx->syntaxError
    // which prints line and so on
    ctx->error = true;
    fprintf(stderr, "Syntax error\n");
}

%parse_failure {
    //same here
    ctx->error = true;
    fprintf(stderr,"Giving up. Parser is hopelessly lost...\n");
}

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
