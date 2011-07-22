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

/// Package Definition Filename
static const char* const PKGDEFFILE = "pkgdef";

/// Package Database Entry Filename
static const char* const PKGDBFILE = "pkgdb";

/// Package Build Result Filename
static const char* const PKGBUILDFILE = "pkgbuild";

/// Current libpkto Version
static const char* const LIBPKTO_VERSION = "0.0.1";

/**
* Define functionalty for a libpkto handle
* Also a small security check
*/
typedef enum pkto_handle_option
{
    /// Allow all functions
    PKTO_HANDLE_ALL = 0xFFFF,
    /// Allow package management
    PKTO_HANDLE_PACKAGE_MANAGEMENT = 4,
    /// Allow repository management
    PKTO_HANDLE_REPOSITORY_MANAGEMENT = 2,
    /// Allow only building of packages
    PKTO_HANDLE_BUILD_ONLY = 1,
    /// Allow only functions which doesn't effect system
    PKTO_HANDLE_NONE = 0
    
} pkto_handle_option;

//TODO Naming for pkto handle options
//TODO Fix flags for pkto options
//TODO Transactions can be interuppted (signals from applications)

/**
* Central File Structure
*/
typedef struct 
{
    /// Mode - Which methods are allowed to execute
    pkto_handle_option mode;
    
    //target directory (e.g. root /)
    //repositories
    //general configuration
    //state
    //thread management?
    //logging?
    //status of handle? missing configuration?
    
    //transactions and state
    
    //error handler function?
    ///PKTO Error Callback
    pkto_error_handler error_handler;
    
} pkto_handle;


/**
* Create a new pkto handle
*/
pkto_handle* pkto_handle_new(pkto_handle_option mode);

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
