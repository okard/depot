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
    
    Directory Functions
*/
#include <osal/dir.h>

#include <osal/mem.h>


//temp debug
#include <stdio.h> 

#include <assert.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>


/**
* posix dir structure
*/
typedef struct os_dir
{
    DIR* dir;
} os_dir;

/**
* posix dir entry structure
*/
typedef struct os_dir_entry
{
    struct dirent* entry;
} os_dir_entry;


/**
* Create new dir object
*/
os_dir* os_dir_new()
{
    os_dir* dir = os_alloc_null(sizeof(os_dir));
    //TODO Initialize Structure here
    return dir;
}

/**
* Delete dir object
*/
void os_dir_delete(os_dir* dir)
{
    os_free(dir);
}

/**
* Open a dir
*/
bool os_dir_open(os_dir* dir, char* path)
{
    return false;
}

/**
* Get next entry
*/
bool os_dir_next(os_dir* dir, os_dir_entry* entry)
{
    assert(dir != NULL);
    assert(entry != NULL);
    
    return false;
}

/**
* Get file size
*/
size_t os_get_filesize(char* path)
{
    struct stat st;
    int result = stat(path, &st);
    if(result == -1)
    {
        fprintf(stderr, "Error getting filesize of %s", path);
        return -1;
    }
    
    return st.st_size;
}

/**
* Is path a directory
*/
bool os_is_dir(char* path)
{
    DIR* dir = opendir(path);
    if(dir == NULL)
        return false;
    
    closedir(dir);
    return true;
}