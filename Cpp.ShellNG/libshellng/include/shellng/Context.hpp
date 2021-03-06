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
#ifndef __SHELLNG_CONTEXT__
#define __SHELLNG_CONTEXT__


namespace sng {
    
//parse context
//  vs execution context
   
/**
* Actual Context
* (is a symboltable?)
*/
class Context
{  
private:
    //Shell&
    //Source&
    
    //SymbolTable 
    //std::map<string, DeclNode>
    
    //Root Context 
		//std::shared_ptr<Context> root_; //weak_ptr?
		
    //Child contexts 
		//mapped to Nodes?
		//std::vector<std::shared_ptr<Context>> childs_;
			
    //parent contexts 
		//std::shared_ptr<Context> parent_;
    
    //Context* nested contextes, stack of contexts?
    
    //node* ast
    
    //Enviroment Variables for processes and so on (is a object in root context
    
    //objects
    //variables (objects, numbers, strings)
public:
    
};
    
}


#endif
