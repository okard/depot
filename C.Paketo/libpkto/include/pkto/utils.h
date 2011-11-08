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
    
    Utility Functions
*/
#pragma once
#ifndef __LIBPKTO_UTILS_H__
#define __LIBPKTO_UTILS_H__

#include <stdlib.h>

/**
* \defgroup Utils Utility Functions
* @{
*/

/**
* A Buffer 
* (Move to libcpr?)
*/
typedef struct pkto_buffer
{
    void* data;
    size_t size;
} pkto_buffer;

/**
* Create a new buffer
*/
pkto_buffer* pkto_buffer_new(size_t size);

/**
* Delete Buffer
*/
void pkto_buffer_delete(pkto_buffer* buffer);


/** }@ */

#endif