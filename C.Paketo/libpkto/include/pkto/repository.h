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
#pragma once
#ifndef __LIBPKTO_REPOSITORY_H__
#define __LIBPKTO_REPOSITORY_H__

#include <pkto/handle.h>

/**
* \defgroup Repository Repository Handling
* @{
*/

//Types
// DB   //only meta data, informations
// BIN  //binary package
// SRC  //src packages
// DEV  //dev packages -> folders with build files



/**
* Holds a repository
*/
typedef struct
{
    /// Pkto Handle
    pkto_handle* handle;
    
    //repository type src/bin
    //repository arch type
    //repository name
    
    // db dir
    // pkg files (cache) src/src-full/bin
    
    ///Cache Database
    KCDB* db;
    
    // json file with all packages for rebuild db and so on
    //folder of pkg cache
} pkto_repository;

//actions sync
//open

//get package from repository

//pkto_repository* pkto_repository_new(pkto_handle* handle);

//open
//search



/** }@ */

#endif
