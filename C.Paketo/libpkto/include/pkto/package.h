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
#ifndef __LIBPKTO_PACKAGE_H__
#define __LIBPKTO_PACKAGE_H__

/**
* \defgroup Package Package Handling
* @{
*/

/**
* Represents a package
*/
typedef struct pkto_package
{
    //From Database
    //- name
    //- version
    //- license
    //- is_oss /is_tainted
    //- arch
    //- signature
    //- deps
    //- repository
    
    //meta?     - a package can be a empty meta package only dependencies
    //multiple? - a package can provide multiple packages (meta(bin) or splitted(src))
    
    //installed? installed as dep not installed
    
    //other files
    //archive_file (bin/src/src-full)
    //-bin file
    //-src file
    //-src-full file
    
    //mirrors?
    
    //From Archive File?
    
}  pkto_package;


/**
* Result of a package action
*/
typedef struct pkto_package_result
{
    //successful
    //error
    //msg
} pkto_package_result;



//open package from repository (handle, repository, name) to repository?
//pkto_package* pkto_package_openrep(pkto_handle* handle, pkto_repository* repo, char* const name);

//open package from archive file (handle, path)
//pkto_package* pkto_package_open(pkto_handle* handle, char* const path);


//open package
    // -> Package Definition pkgdef (run build process)
    // -> Package Defintion Folder  (run build process)
    // -> Bin Archive               (handle file)
    // -> Src Archive (Clean or Full Src)

    //look first for a  pkgdb file
    //if one available load information about package
    //if only pkgdef start build process nothing else possible?
    //build process api to package informationens?

    //pkgdef  - Package Defintion (Handled by build process)
    //pkgdb   - Package DB Entry  (Created by build process) JSON ?

/** }@ */

#endif
