
%token_prefix {TOKEN_}

%token_type { Token* }

// also can make callbacks to notifier about parsing states
//%extra_argument { Context *ctx }


%type program { Node* }


%include {
#include <cstdio>
#include <cassert> /* required for building */
#include <shellng/Token.hpp>
#include <shellng/Ast.hpp>
#include <shellng/Context.hpp>
using namespace sng;
}


%syntax_error {
    //call error on extra argument
    // ctx->syntaxError
    // which prints line and so on
    fprintf(stderr, "Syntax error\n");
}

%parse_failure {
    //same here
    fprintf(stderr,"Giving up. Parser is hopelessly lost...\n");
}

%start_symbol program

program(p) ::= INTEGER(a). {
    a->integer=0;
    p = new Node();

    //ctx->onParseEvent(p);
    //ctx->interpret(p);
}

program(p) ::= KW_DEF. {
    p = new Node();
}

/*
program ::= def
program ::= com

com ::= 

com ::= IDENTIFIER ARGS
*/
