/*
    This file is part of libpkto.

    libpkto is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with libpkto.  If not, see <http://www.gnu.org/licenses/>.
    
    Platform independent function which are not available in standard c library
*/
#ifndef __LIBPKTO_OS_H__
#define __LIBPKTO_OS_H__

///////////////////////////////////////////////////////////////////////////////
// IO - Directory Reading

//size_t os_getfilesize(char* path);

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
void os_process_start(os_process* proc, char* process);

/**
* Wait until child process finished
*/
void os_process_wait(os_process* proc);



#endif
