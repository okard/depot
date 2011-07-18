/*
    This file is part of libpkto.

    libpkto is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    libpkto is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with libpkto.  If not, see <http://www.gnu.org/licenses/>.
    
    Platform independent function which are not available in standard c library
*/
#ifndef __LIBPKTO_OS_H__
#define __LIBPKTO_OS_H__

#include <stddef.h>
#include <stdbool.h>

///////////////////////////////////////////////////////////////////////////////
// General

/**
* OS Layer Error Callback
*/
typedef void(*os_error_handler)(int errorid, const char* msg, void* ctx);

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

/**
* Get next entry
*/
os_dir_entry* os_dir_next(os_dir* dir);

//TODO lesser memory consume new/delete/clean for os_dir_entry

/**
* Get file size
*/
size_t os_get_filesize(char* path);

//char* os_get_executabledir();
// char *getcwd(char *buf, size_t size);
// int chdir(const char *path);


///////////////////////////////////////////////////////////////////////////////
// Process Handling
typedef struct os_process os_process;

/**
* Create a new process object
*/
os_process* os_process_new();

/**
* Delete process object
*/
void os_process_delete(os_process* proc);

/**
* Start a process
*/
void os_process_start(os_process* proc, const char* path, const char *arg0, ...);
//TODO arguments?
//TODO env?

//Flags for stdin/out/err mapping?
//Write to process stdin
//Event Callbacks

//void os_process_seterrhandler(os_process* proc, os_error_handler handler, void* ctx);

/**
* Wait until child process finished
*/
void os_process_wait(os_process* proc);



#endif
