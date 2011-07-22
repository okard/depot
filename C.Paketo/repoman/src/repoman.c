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

#include <pkto/pkto.h>

#include "repoman.h"

//TODO Program Signal handling

/**
* Parsed repoman arguments
* Helper Structure
*/
typedef struct repoman_args
{
    //build a specific folder
    bool folder_build;
    //build specific folder recursive
    bool folder_build_recursive;
    //the folder to build
    char* folder;
    //print out version information
    bool print_version;
} repoman_args;

/**
* Print Usage
*/
static void usage()
{
    printf("Usage:\n");
    printf("repoman build <dir>\n");
    printf("repoman <config>\n");
    printf("repoman daemon <config>\n");
    
    //upload to repository??
}

/**
* parse arguments
*/
void parse_args(int argc, char *argv[], repoman_args* rargs)
{
    //TODO implement repoman parse_args
}


/**
* Main Function
*/
int main(int argc, char *argv[])
{
    //TODO parse arguments
    repoman_args rargs;
    parse_args(argc, argv, &rargs);
    
    
    printf("repoman version: %s\n", REPOMAN_VERSION);
    printf("libpkto version: %s\n\n", LIBPKTO_VERSION);
    
    if(argc < 2)
    {
        printf("Error: to less arguments\n");
        //print usage
        usage();
        return 1;
    }
    
    //initialize pkto_core
    pkto_handle* handle = pkto_handle_new();
    
    //parse config
    
    
    //build command
    if(strcmp(argv[1], "build") == 0)
    {
        if(argc >= 3)
        {
            //TODO Sign, package requires signature for building
            printf("Start building %s\n", argv[2]);
            pkto_build(handle, argv[2]);
            return 0;
        }
        else
        {
            printf("Syntax: %s build <folder>\n", argv[0]);
            //print usage
            usage();
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