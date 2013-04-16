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
#ifndef __SHELLNG_TOKEN__
#define __SHELLNG_TOKEN__

#include <string>

#include <shellng/Types.hpp>
#include <shellng/String.hpp>

namespace sng {
	
//enum class

enum class TokenID : ubyte8
{
	TOKEN_UNKOWN,
	TOKEN_IDENTIFIER,	   	//<identifier>
	TOKEN_IDENTIFIER_ID,   	//$<identifier>
	TOKEN_IDENTIFIER_COM,  	//identifier xxx
	TOKEN_NUMBER,
	String,					// "string"
	
	TOKEN_PLUS,				//+
	TOKEN_MINUS,			//-
	TOKEN_MUL,				//*
	TOKEN_DIV,				// /
	
	Assign,					// =
	
	// =
	// ==
	// &
	// &&
	// |
	// ||
	// >
	// >>
	// <
	
	Colon,	 		 // :
	Dot,			 // .
	Semicolon,		 // ;
	
	TOKEN_COBRACKET, // {
	TOKEN_CCBRACKET, // }
	TOKEN_ROBRACKET, // (
	TOKEN_RCBRACKET, // )
	TOKEN_SOBRACKET, // [
	TOKEN_SCBRACKET, // ]
	
	TOKEN_KW_DEF,    // def
	TOKEN_KW_OBJECT, // object
	TOKEN_KW_IF,
	TOKEN_KW_ELSE,
	TOKEN_KW_FOR,
	TOKEN_KW_WHILE,
	
	TEOL,		//end of line also required
	TEOF			//no more token available
};
    
/**
* Token
*/
struct Token
{
    TokenID id;
    
    //change to internal string
    std::string value;
};






}
#endif //__SHELLNG_TOKEN__
