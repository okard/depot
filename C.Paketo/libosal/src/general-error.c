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
#include <osal/error.h>

#include <osal/mem.h>

/**
* Create new error object
*/
os_error* os_error_new(int id, const char* const msg, void* ctx)
{
    os_error* err = os_alloc_null(sizeof(os_error));
    err->id = id;
    err->msg = (char*)msg;
    err->ctx = ctx;
    
    return err;
}

/**
* Create new error object by id
*/
os_error* os_error_new_byid(os_error_id id, const char* const msg, void* ctx)
{
    return os_error_new(id, msg, ctx);
}

/**
* Freeing Error
*/
void os_error_free(os_error* err)
{
    //TODO freeing msg also?
    //TODO add flag for freeing msg?
    os_free(err);
}
