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
    
    This File contains basic functions for libpkto
*/
#include <pkto/pkto.h>

#include <osal/mem.h>


/**
* Create new pkto object
*/
pkto_handle* pkto_handle_new(pkto_handle_option mode)
{
    pkto_handle* obj = os_alloc_null(sizeof(pkto_handle));
    //initialize structure here
    obj->error_handler = NULL;
    obj->mode = mode;
    return obj;
}

/**
* Delete a pkto object
*/
void pkto_handle_delete(pkto_handle* obj)
{
    os_free(obj);
}