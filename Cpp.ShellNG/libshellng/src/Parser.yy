
%token_prefix {TOKEN_}

%token_type { Token* }

// also can make callbacks to notifier about parsing states
//%extra_argument { ParserState *state }


%type program { Node* }


%include {
#include <cstdio>
#include <cassert> /* required for building */
#include <shellng/Token.hpp>
#include <shellng/Ast.hpp>
using namespace sng;
}


%syntax_error {
    fprintf(stderr, "Syntax error\n");
}

%parse_failure {
    fprintf(stderr,"Giving up. Parser is hopelessly lost...\n");
}

%start_symbol program

program(p) ::= INTEGER. {
    p = new Node();
}

