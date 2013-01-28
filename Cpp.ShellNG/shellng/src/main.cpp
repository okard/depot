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

#include <cstring>
#include <iostream>

#include <shellng/Shell.hpp>
#include <shellng/Source.hpp>

#include "LineSource.hpp"

using namespace sng;

int main(int argc, char **argv)
{
	
	Shell shell;
    std::shared_ptr<Source> source;
    
    //parse arguments
    //- "-f" execute script file 
    if(argc == 3 && !strncmp("-f", argv[1], 2))
    {
        //open file from argv[2] as source and executes it
		source.reset(new SourceFile());
		static_cast<SourceFile*>(source.get())->open(argv[2]);
    }
    else
		source.reset(new LineSource(shell));
		
    
   
        //create interactive stdin jobs and enqueue it
        
        //read into buffer from line until it can successful parsed
        // Use a quiet errr parsing context
        // successful ast creation get executed in rootContext? 
            //aka succesful ast becoming a job in event loop
            
        //add a idle job that executes LineSource File
        
        shell.execute(source);
        shell.dispatch();
    
    //shell event loop

    
    return 0;
}
