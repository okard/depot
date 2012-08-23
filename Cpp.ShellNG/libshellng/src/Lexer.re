

#pragma once
#ifndef __LEXER_RE2C__
#define __LEXER_RE2C__

#include <cstdio>

// TOKENS are generated by lemon parser generator
// so re2c depends on lemon
// weird to have first parser then lexer dependency

#include "Parser.h"


unsigned int Lexer::next(Token& tok)
{
std:
        m_token = m_cursor;

    /*!re2c
        re2c:define:YYCTYPE = "char";
        re2c:define:YYCURSOR = m_cursor;
        re2c:define:YYMARKER = m_marker;
        re2c:define:YYLIMIT = m_limit;
        re2c:define:YYFILL:naked = 1;
        re2c:define:YYFILL@len = #;
        re2c:define:YYFILL = "if (!fill(#)) { return 0; }";
        re2c:yyfill:enable = 1;
        re2c:indent:top = 2;
        re2c:indent:string=" ";

        INTEGER = [1-9][0-9]*;
        WS = [ \r\n\t\f];
        ANY_CHARACTER = [^];

        INTEGER {
            tok.integer = 0;
            //yylval.int_value = atoi(this->text().c_str());
            return TOKEN_INTEGER;
        }
        "def" { 
            return TOKEN_KW_DEF; 
        }
        WS {
            goto std;
        }
        ANY_CHARACTER {
            printf("unexpected character: '%c(%d)'\n", *m_token, *m_token);
            goto std;
        }

    */
}

/*
        "def" { return TOKEN_KW_DEF; }
*/



#endif

