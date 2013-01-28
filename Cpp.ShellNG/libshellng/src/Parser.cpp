/*
Copyright (c) 2013 okard

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

#include <shellng/Parser.hpp>

#include <cassert>
#include <iostream>

#include <shellng/Exception.hpp>

using namespace sng;


Parser::Parser()
	: token_(5), tokenIndex_(0)
{
}

Parser::~Parser()
{
	
}
	
	

NodePtr Parser::parse()
{
	//initial token
	nextTok();
	
	if(curTok().id == TOKEN_KW_DEF)
		return parseDeclaration();
	else
		return parseStatement();
	
	//else return parseStatement
	
	NodePtr ptr(new Node());
	
	return ptr;
}

Token& Parser::curTok()
{
	return token_[tokenIndex_];
}

Token& Parser::nextTok()
{
	//TODO check token index
	lexer_.next(token_[tokenIndex_]);
}


NodePtr Parser::parseDeclaration()
{
	//def identifier : <type> ...
	std::cout << "parseDeclaration()" << std::endl;
	assert(curTok().id == TOKEN_KW_DEF);
	
	//save tokenIndex_
	tokenIndex_++;
	if(nextTok().id != TOKEN_IDENTIFIER)
	{
		throw Exception("parseDeclaration(): Expected IDENTIFIER");
	}
	
	tokenIndex_++;
	if(nextTok().id != TOKEN_COLON)
	{
		throw Exception("parseDeclaration(): Expected COLON");
	}
	
	//switch over declaration type
	switch(nextTok().id)
	{
		case TOKEN_KW_OBJECT:
			break;
		
		//object
		//function
		//string
		//number
		//clone $idexpr
			
		default:
			throw Exception("parseDeclaration(): Invalid definition type");
	}
	
	NodePtr decl(new Decl());
	return decl;
}


NodePtr Parser::parseStatement()
{
	std::cout << "parseStatement()" << std::endl;
	
	switch(curTok().id)
	{
		case TOKEN_KW_IF:
			return parseIfStatement();
		case TOKEN_KW_FOR:
			return parseForStatement();
		//case TOKEN_KW_WHILE:
		//	
	}
	
	//if Identifier_ID
	//else 
	//parse expr
	
	
	NodePtr stmt(new Stmt());
	return stmt;
}

NodePtr Parser::parseIfStatement()
{
	NodePtr stmt(new IfStmt());
	return stmt;
}

NodePtr Parser::parseForStatement()
{
	NodePtr stmt(new ForStmt());
	return stmt;
}

NodePtr Parser::parseCommandStatement()
{
	NodePtr stmt(new Stmt());
	return stmt;
}

NodePtr Parser::parseExpression()
{
	//if $expr a normal expression
	
	//if number
	//else commandExpression
	
	
	NodePtr expr(new Expr());
	return expr;
}

NodePtr Parser::parseBinaryExpression()
{
	NodePtr expr(new Expr());
	return expr;
}
