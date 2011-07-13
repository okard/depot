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
*/
#include <pkto/os.h>

#include <stdlib.h>

//Implement os specific (non ansi c99) here for posix

/**
* Posix Process Structure
*/
typedef struct os_process
{
    
} os_process;


/**
* Create a new process object
*/
os_process* os_process_new()
{
    os_process* proc = malloc(sizeof(os_process));
    //TODO Initialize Structure here
    return proc;
}

/**
* Delete process object
*/
void os_process_delete(os_process* proc)
{
    free(proc);
    proc = 0;
}

/**
* Start a process
*/
void os_process_start(os_process* proc, char* process)
{
    //fork
    //exec
    
}