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

#include <pkto/pkto.h>

#include "paketo.h"


/**
* Print usage
*/
static void usage()
{
    printf("Usage: \n");
    
}


/**
* Main Function
*/
int main(int argc, char *argv[])
{
    printf("paketo\n");
    
    //install --src <package>
    //remove <package>
    //search <package>
    //sync [<repository>] 
    //upgrade [<package>]
    
    //update -> sync + upgrade

    //build <folder>
    //grab <package> target <folder>
    
    // for user builds
    // grab/source/pkgdef/download - download source
    // quit
    
    //web server api for requesting packages
    //representing something like aur dont sync complete db but get/search for a specific package
    
}