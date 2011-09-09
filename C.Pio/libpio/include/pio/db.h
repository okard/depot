/*
    Personal Information Objects
    
    Copyright (c) 2011  okard

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
    
    PIO Database
*/
#ifndef __LIBPIO_DB_H__
#define __LIBPIO_DB_H__

#include <pio/objects.h>

/**
* Pio Database
*/
typedef struct pio_db pio_db;

/**
* Open pio database
*/
pio_db* pio_db_open(char* path);

/**
* Close pio database
*/
void pio_db_close(pio_db* db);

/**
* Retrieve a pio from db
*/
piobj* pio_db_read(pio_db* db, pioid id);

/**
* Write a object to db
*/
void pio_db_write(pio_db* db, piobj* obj);

/**
* Update a pio in db
*/
void pio_db_update(pio_db* db, piobj* obj);



#endif