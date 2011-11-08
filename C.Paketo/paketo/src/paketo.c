/*
    This file is part of paketo.

    paketo is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    paketo is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with paketo. If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>

#include <pkto/handle.h>

#include "paketo.h"

//TODO Program Signal handling


/**
* Print usage
*/
static void usage(char* exec)
{
    printf("Usage: \n");
    printf("%s install [--src] <package>\n", exec);
    printf("%s remove <package>\n", exec);
    printf("%s search <package>\n", exec);
    printf("%s status <package>\n", exec);
    printf("%s sync [<repository>]\n", exec);
    printf("%s upgrade [<package>]\n", exec);
    printf("%s update\n", exec);
    printf("%s build [-i] <folder>\n", exec);
    
    //build <folder>
    //grab <package> target <folder>
}

//parse args function

/**
* Main Function
*/
int main(int argc, char *argv[])
{
    printf("paketo\n");
    
    if(argc < 2)
    {
        usage(argv[0]);
        return 1;
    }
    
    //detect action
    
    //create pkto handle

    
    // for user builds
    // grab/source/pkgdef/download - download source
    // quit
    
    //web server api for requesting packages
    //representing something like aur dont sync complete db but get/search for a specific package
    
}