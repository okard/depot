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
    
    Error Functions
*/
#ifndef __LIBOSAL_ERROR_H__
#define __LIBOSAL_ERROR_H__

/**
* \defgroup Error Error Handling
* @{
*/

/**
* Default error ids
*/
typedef enum os_error_id
{
    OS_ERROR_NO_ERROR = 0,
    OS_ERROR_UNKOWN = 1,
    
    //Process Module Errors
    OS_ERROR_PROCESS,
    
    OS_ERROR_MAXID
} os_error_id;

/**
* Error Structure
*/
typedef struct os_error
{
    int id;
    char* msg;
    void* ctx;
} os_error;

/**
* OS Layer Error Callback
*/
typedef void(*os_error_handler)(os_error* err);


/**
* Create new error object
*/
os_error* os_error_new(int id, const char* const msg, void* ctx);

/**
* Create new error object by id
*/
os_error* os_error_new_byid(os_error_id id, const char* const msg, void* ctx);

/** }@ */

#endif
