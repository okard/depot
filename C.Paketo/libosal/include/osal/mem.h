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
    
    Memory Functions
*/
#ifndef __LIBOSAL_MEM_H__
#define __LIBOSAL_MEM_H__

#include <stddef.h>

/**
* \defgroup Mem Memory Handling
* @{
*/

/**
* Allocate Memory
*/
void* os_alloc(size_t size);

/**
* Allocate memory and set it to null
*/
void* os_alloc_null(size_t size);

/**
* Freeing memory
*/
void os_free(void* mem);


/** }@ */

#endif 