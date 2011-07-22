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
*/
#ifndef __LIBPKTO_PKTO_H__
#define __LIBPKTO_PKTO_H__

#include <pkto/error.h>

/**
* \defgroup PKTO Paketo Library Core
* @{
*/


// Constants
static const char* const PKGDEFFILE = "pkgdef";
static const char* const PKGDBFILE = "pkgdb";
static const char* const PKGBUILDFILE = "pkgbuild";
static const char* const LIBPKTO_VERSION = "0.0.1";


//OPTIONS for creating handle (build_only/package_management/repository_management....)

//TODO Transactions can be interuppted (signals from applications)

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
    //status of handle? missing configuration?
    
    //error handler function?
    ///PKTO Error Callback
    pkto_error_handler error_handler;
    
} pkto_handle;


/**
* Create a new pkto handle
*/
pkto_handle* pkto_handle_new();

/**
* Delete a pkto handle
*/
void pkto_handle_delete(pkto_handle* handle);

/**
* Read libpkto configuration file
*/
void pkto_read_config(pkto_handle* handle, char* file);

//request setting?
//char* pkto_get_setting(handle, char* id)

/**
* Build a package
*/
void pkto_build(pkto_handle* handle, char* path);

//add repository to core

//other functions

// Package DB
// Package - Install / Remove / Status
// Repository - Configs


/** }@ */

#endif
