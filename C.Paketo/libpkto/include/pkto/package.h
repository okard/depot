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
#ifndef __LIBPKTO_PACKAGE_H__
#define __LIBPKTO_PACKAGE_H__

typedef struct pkto_package
{
    //name
    //version
    //repository
    //arch
    
};


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

#endif