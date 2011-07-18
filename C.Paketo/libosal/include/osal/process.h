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
    
    Process Functions
*/
#ifndef __LIBOSAL_PROCESS_H__
#define __LIBOSAL_PROCESS_H__

#include <osal/error.h>

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