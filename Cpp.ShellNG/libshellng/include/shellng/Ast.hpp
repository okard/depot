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
#ifndef __SHELLNG_AST__
#define __SHELLNG_AST__

#include <memory>
#include <vector>
#include <string>



namespace sng {
	

	
//std::shared_ptr

/**
* Basic Node
*/
class Node
{
public:
    enum NodeType
    {
        //Declarations
        DECL_VARIABLE,
        DECL_FUNCTION,
        DECL_OBJECT,
        
        //Expressions
        TYPE_COMMAND,
    };
    
    
    NodeType type;
    
    //type
};

//ast ptr
typedef std::shared_ptr<Node> NodePtr;

//weak NodePtr?


class Program : public Node
{
	//list of nodes
};

/**
* Basic Declaration Node
*/
class Decl : public Node
{
    
};

/**
* Variable Declaration
* def foo: string
*/
class VarDecl : public Decl
{
public:
    //name
    //type
    //dynamic
};

/**
* Function Declaration
* def abc: function(a,b,c)
*/
class FuncDecl : public Decl
{
	//has a new context
};

/**
* Object Declaration
* def foo: object 	//new
* def foo: $id		//clone
*/
class ObjDecl : Node
{
    //Function
    //Variables
    
    //has a new context
};


class Stmt : public Node
{
};


class IfStmt : public Stmt
{
};

class ForStmt : public Stmt
{
};

class WhileStmt : public Stmt
{
};

class ExprStmt : public Stmt
{
	NodePtr expr;
};

/**
* Basic Expression Node
*/
class Expr : public Node
{
};

//Literal Expression

/**
* Binary Expression
*/
class BinaryExp : public Expr
{
	//ShellOP | > < >> << ||
    //BinOP + - * / ~ 
	enum Operator
	{
		OP_ASSIGN, //=
		OP_PLUS,   //+
	};
	
	Operator op;
	NodePtr left;
	NodePtr right;
};

/**
* Command Expression
* Executes a command/program
*/
class CommandExp : public Expr
{
	//arguments can be expressions
	std::vector<std::string> args;
    //file
    //args
};

} //end namespace sng

#endif
