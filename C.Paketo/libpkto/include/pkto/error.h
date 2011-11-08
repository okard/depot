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
    
    error ids
*/
#pragma once
#ifndef __LIBPKTO_ERROR_H__
#define __LIBPKTO_ERROR_H__

#include <cpr/error.h>

/**
* \defgroup Error Error Handling
* @{
*/


/**
* ERROR IDs
* The libpkto error ids starts after the libosal errors
* Only the "No Error" id is the same as in libosal
*/
typedef enum pkto_error
{
    /// No Error occurred
    PKTO_NO_ERROR = CPR_ERROR_NO_ERROR,
    /// Unkown Error
    PKTO_ERROR_UNKOWN = CPR_ERROR_MAXID+1,
    
    
    PKTO_ERROR_MAXID
} pkto_error;


/**
* PKTO Error Handler Callback
*/
typedef void(*pkto_error_handler)(pkto_error error, const char* msg);

/**
* Get String Message for Error 
*/
char* pkto_strerror(pkto_error error);


/** }@ */

#endif