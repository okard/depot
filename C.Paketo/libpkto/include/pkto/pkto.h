/*
    This file is part of libpkto.

    libpkto is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with libpkto.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef __LIBPKTO_PKTO_H__
#define __LIBPKTO_PKTO_H__

// Constants
#define PKGDEFFILE "pkgdef"
#define PKGDBFILE "pkgdb"
#define PKGBUILDFILE "pkgbuild"

static const char* const libpkto_version = "0.0.1";


/**
* Central File Structure
*/
typedef struct 
{
    //target directory (e.g. root /)
    //repositories
    //general configuration
    //state
    //thread management?
    //logging?
    
    //error handler function?
} pkto_handle;


/**
* Create a new pkto handle
*/
pkto_handle* pkto_handle_new();

/**
* Delete a pkto handle
*/
void pkto_handle_delete(pkto_handle* handle);


//add repository to core


//other functions

/**
* Build a package
*/
void pkto_build(pkto_handle* handle, char* path);


// Package DB
// Package - Install / Remove / Status
// Repository - Configs


#endif
