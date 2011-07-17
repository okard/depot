/*
    This file is part of repoman.

    libpkto is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with repoman.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <string.h>

#include <pkto/pkto.h>


/**
* Main Function
*/
int main(int argc, char *argv[])
{
    printf("repoman\n");
    printf("libpkto version: %s\n", LIBPKTO_VERSION);
    
    if(argc < 2)
    {
        //print usage
        printf("Error: to less arguments\n");
        return 1;
    }
    
    //initialize pkto_core
    pkto_handle* handle = pkto_handle_new();
    
    //build command
    if(strcmp(argv[1], "build") == 0)
    {
        if(argc >= 3)
        {
            printf("Start building %s\n", argv[2]);
            pkto_build(handle, argv[2]);
            return 0;
        }
        else
        {
            printf("Syntax: %s build <folder>\n", argv[0]);
            return 1;
        }
    }
    
    
    //options:
    //run on repository-root.json config file
    //run on complete folder
        //-each subfolder should contain a pkgdef
    //run on single folder (containing pkgdef) 
    //daemon mode
    
    // build 
    
    pkto_handle_delete(handle);
    
}