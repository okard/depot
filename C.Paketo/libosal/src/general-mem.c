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
#include <osal/mem.h>

#include <stdlib.h>
#include <string.h>

/**
* Allocate Memory
*/
void* os_alloc(size_t size)
{
   return malloc(size); 
}

/**
* Allocate memory and set it to null
*/
void* os_alloc_null(size_t size)
{
    void* mem = os_alloc(size);
    memset(mem, 0, size);
    return mem;
}


/**
* Freeing memory
*/
void os_free(void* mem)
{
    free(mem);
    mem = 0;
}
