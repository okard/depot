/*
    This file is part of repoman.

    repoman is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    repoman is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with repoman.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>

#include <pkto/handle.h>
#include <pkto/error.h>
#include <pkto/action.h>

#include "repoman.h"

//TODO Program Signal handling


/**
* Print Usage
*/
static void usage(char* exec)
{
    printf("Usage:\n");
    printf("%s build <dir>\n", exec);
    printf("%s <config>\n", exec);
    printf("%s daemon <config>\n", exec);
    
    //upload to repository??
    //--config file.conf
}

/**
* parse arguments
*/
void parse_args(int argc, char *argv[], repoman_args* rargs)
{
    //TODO implement repoman parse_args
}

/**
* pkto error handler
*/
void pkto_handle_error_handler(pkto_error error, const char* msg)
{
    fprintf(stderr, "%s: %s\n", pkto_strerror(error), msg);
}


/**
* Handle SIGINT
*/
void sigint_handler()
{  
   //signal(SIGINT,sigint); /* reset signal */
   //printf("CHILD: I have received a SIGINT\n");
   printf("sigint occured\n"); 
   //interrupt pkto
   
}


/**
* Main Function
*/
int main(int argc, char *argv[])
{
    //register signal handler
     signal(SIGINT, sigint_handler);
    
    //TODO parse arguments
    repoman_args rargs;
    parse_args(argc, argv, &rargs);
    
    printf("repoman version: %s\n", REPOMAN_VERSION);
    printf("libpkto version: %s\n\n", LIBPKTO_VERSION);
    
    if(argc < 2)
    {
        printf("Error: to less arguments\n");
        //print usage
        usage(argv[0]);
        return 1;
    }
    
    ///////////////////////////////////////////////////////////////////////////
    //initialize pkto_core
    pkto_handle* handle = pkto_handle_new(PKTO_HANDLE_REPOSITORY_MANAGEMENT);
    pkto_handle_set_error_handler(handle, &pkto_handle_error_handler);
    
    //parse config
    
    
    //build command
    if(strcmp(argv[1], "build") == 0)
    {
        if(argc >= 3)
        {
            //TODO Sign, package requires signature for building
            printf("Start building %s\n", argv[2]);
            
         
            //create build action
            pkto_action_build ba;
            ba.handle = handle;
            ba.path = argv[2];
            //rm_prepare(&ba);
            
            //start build
            pkto_build(&ba);
            
            return 0;
        }
        else
        {
            printf("Syntax: %s build <folder>\n", argv[0]);
            //print usage
            usage(argv[0]);
            return 1;
        }
    }
    
    
    //options:
    //run on repository-root.json config file        
    //run on single folder (containing pkgdef) 
    //daemon mode
    
    //Create Package DB?
    
    // build 
    
    pkto_handle_delete(handle);
    
}