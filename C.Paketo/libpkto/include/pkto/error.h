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
#ifndef __LIBPKTO_ERROR_H__
#define __LIBPKTO_ERROR_H__


/**
* ERROR IDs
*/
typedef enum pkto_error
{
    PKTO_NO_ERROR = 0,
    PKTO_ERROR_UNKOWN = 1
} pkto_error;


/**
* PKTO Error Handler Callback
*/
typedef void(*pkto_error_handler)(pkto_error error, const char* msg);

/**
* Get String Message for Error 
*/
char* pkto_strerror(pkto_error error);


#endif