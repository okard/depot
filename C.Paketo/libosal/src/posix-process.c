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
#include <osal/process.h>

#include <osal/mem.h>
#include <osal/error.h>

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
* Posix Process Structure
*/
typedef struct os_process
{
     /// Process ID
     pid_t pid;
     //process status?
     int result;
     
     /// Error Handler Callback
     os_error_handler error_handler;
     /// Error Context
     void* error_context;
} os_process;




/**
* Create a new process object
*/
os_process* os_process_new()
{
    os_process* proc = os_alloc_null(sizeof(os_process));
    //TODO Initialize Structure here
    proc->error_handler = NULL;
    return proc;
}

/**
* Delete process object
*/
void os_process_delete(os_process* proc)
{
    os_free(proc);
}

/**
* Set error handler
*/
void os_process_set_error_handler(os_process* proc, os_error_handler handler, void* ctx)
{
    proc->error_context = ctx;
    proc->error_handler = handler;
}

/**
* Fire a error
*/
static void os_process_error(os_process* proc, int id, const char* const msg)
{
    if(proc->error_handler != NULL)
    {
        os_error* err = os_error_new(id, msg, proc->error_context);
        (*proc->error_handler)(err);
        
        //if user accidently delete err
        if(err != 0)
            os_error_free(err);
    }   
}

/**
* Start a process
*/
void os_process_start(os_process* proc, const char* path, const char* args[])
{
    //fork (vfork here?)
    proc->pid = fork();
    
    if(proc->pid < 0)
    {
        //Error
        os_process_error(proc, OS_ERROR_PROCESS, "Error calling fork");
        return;
    }
    
    if(proc->pid > 0)
    {
        //Parent
        return;
    }
    
    //Bind input and output to stdin and stdout?
    //Child Process here
    //int execv (__const char *__path, char *__const __argv[])
    int result = execv(path, args);
    
    //should never go here?
    if(result == -1)
    {
        //save error message first
        char* msg = strerror(errno);
        os_process_error(proc, OS_ERROR_PROCESS, msg);
        //os_free(msg);
        
        os_process_error(proc, OS_ERROR_PROCESS, "Error executing execl");
    }
    
    //Exit forked process?
    _exit(0); 
}


/**
* Wait until child process finished
*/
void os_process_wait(os_process* proc)
{
     int childExitStatus = 0;
     pid_t r = waitpid( proc->pid, &childExitStatus, 0);   
     
     if(WIFEXITED(childExitStatus))
     {
         //Normally exited
         proc->result = WEXITSTATUS(childExitStatus);
     }
}