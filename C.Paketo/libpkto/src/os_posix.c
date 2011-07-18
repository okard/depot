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
*/
#include <pkto/os.h>

#include <stdlib.h>
//temp debug
#include <stdio.h> 

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

//Implement os specific (non ansi c99) here for posix

/**
* posix dir structure
*/
typedef struct os_dir
{
} os_dir;

/**
* posix dir entry structure
*/
typedef struct os_dir_entry
{
    
} os_dir_entry;

/**
* Posix Process Structure
*/
typedef struct os_process
{
     /// Process ID
     pid_t pid;
     //process status?
     
     /// Error Handler Callback
     os_error_handler error_handler;
     /// Error Context
     void* error_context;
} os_process;


/**
* Create new dir object
*/
os_dir* os_dir_new()
{
    os_dir* dir = malloc(sizeof(os_dir));
    //TODO Initialize Structure here
    return dir;
}

/**
* Delete dir object
*/
void os_dir_delete(os_dir* dir)
{
    free(dir);
    dir = 0;
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
os_dir_entry* os_dir_next(os_dir* dir)
{
    return 0;
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
* Create a new process object
*/
os_process* os_process_new()
{
    os_process* proc = malloc(sizeof(os_process));
    //TODO Initialize Structure here
    proc->error_handler = NULL;
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
void os_process_start(os_process* proc, const char* path, const char *arg0, ...)
{
    //fork (vfork here?)
    proc->pid = fork();
    
    if(proc->pid < 0)
    {
        //Error
        fprintf(stderr, "Error calling fork\n");
        return;
    }
    
    if(proc->pid > 0)
    {
        //Parent
        return;
    }
    
    //Bind input and output to stdin and stdout?
    //Child Process here
    int result = execl(path, arg0);
    
    if(result == -1)
    {
        //error calling execl
        fprintf(stderr, "Error calling execl\n");
    }
    
    //Exit forked process?
}


/**
* Wait until child process finished
*/
void os_process_wait(os_process* proc)
{
     int childExitStatus = 0;
     pid_t r = waitpid( proc->pid, &childExitStatus, 0);    
}