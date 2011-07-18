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
#ifndef __LIBOSAL_DIR_H__
#define __LIBOSAL_DIR_H__

#include <stddef.h>
#include <stdbool.h>

///////////////////////////////////////////////////////////////////////////////
// IO - Directory Reading
typedef struct os_dir os_dir;
typedef struct os_dir_entry os_dir_entry;

/**
* Create new dir object
*/
os_dir* os_dir_new();

/**
* Delete dir object
*/
void os_dir_delete(os_dir* dir);

/**
* Open a dir
*/
bool os_dir_open(os_dir* dir, char* path);

//dir_close

/**
* Get next entry
*/
bool os_dir_next(os_dir* dir, os_dir_entry* entry);


//TODO lesser memory consume new/delete/clean for os_dir_entry

/**
* Get file size
*/
size_t os_get_filesize(char* path);

/**
* Is path a directory
*/
bool os_is_dir_(char* path);


//char* os_get_executabledir();
// char *getcwd(char *buf, size_t size);
// int chdir(const char *path);


#endif