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
#include <pio/db.h>

#include <kclangc.h>

#include <cpr/mem.h>

typedef struct pio_db 
{
    KCDB* db;
    
} pio_db;

/**
* Open pio database
*/
pio_db* pio_db_open(char* path)
{
    pio_db* pdb = cpr_alloc_null(sizeof(pio_db));
    
    /* create the database object */
    pdb->db = kcdbnew();

    /* open the database */
    if (!kcdbopen(pdb->db, path, KCOWRITER | KCOCREATE)) 
    {
        //fprintf(stderr, "open error: %s\n", kcecodename(kcdbecode(db)));
    }
}


/**
* Close pio database
*/
void pio_db_close(pio_db* pdb)
{
    /* close the database */
    if (!kcdbclose(pdb->db)) 
    {
       // fprintf(stderr, "close error: %s\n", kcecodename(kcdbecode(db)));
    }

    /* delete the database object */
    kcdbdel(pdb->db);
}

/**
* Retrieve a pio from db
*/
piobj* pio_db_read(pio_db* db, pioid id)
{

    //allocate piobj
    //read header
    //read rest
    /* retrieve a record */
    /*vbuf = kcdbget(db, "foo", 3, &vsiz);
    if (vbuf) {
    printf("%s\n", vbuf);
    kcfree(vbuf);
    } else {
    fprintf(stderr, "get error: %s\n", kcecodename(kcdbecode(db)));
    }*/
}

/**
* Write a object to db
*/
void pio_db_write(pio_db* db, piobj* obj)
{
    //calculate checksum
    //kcdbset(db, "foo", 3, "hop", 3) 
}

/**
* Update a pio in db
*/
void pio_db_update(pio_db* db, piobj* obj)
{
    //update old with a link
    //write new one
}