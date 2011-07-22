/*
    This file is part of libosal.

    libosal is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    libosal is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with libosal.  If not, see <http://www.gnu.org/licenses/>.
    
    Path Functions
*/
#include <osal/path.h>

#include <osal/mem.h>


/// Posix Path Seperator
static const char PATHSEP = '/';

/**
* posix dir structure
*/
typedef struct os_path
{
  char* pathstr;
  size_t mem;
  
  //include os_dir and os_file here?
} os_path;


/**
* Create new path object
*/
os_path* os_path_new()
{
    os_path* path = os_alloc_null(sizeof(os_path));
    static const size_t default_memsize = 1024;
    path->pathstr = os_alloc_null(default_memsize);
    path->mem = default_memsize;
    return path;
}

/**
* Delete path object
*/
void os_path_delete(os_path* path)
{
    os_free(path->pathstr);
    os_free(path);
}

/**
* Get path seperator
*/
char os_path_seperator()
{
    return PATHSEP;
}