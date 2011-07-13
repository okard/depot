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
#include <pkto/pkto.h>

#include <pkto/os.h>


void pkto_build(pkto_handle* handle, char* path)
{
    //opendir
    //look for pkgdef
    //open path + pkgdef
    
    
    //requires pkgdef
    //line ending? map build tool? .sh = bash, .lua = lua and so on?
    //requires folder with pkgdef
    //test if folder is writeable?
    //build to temp if not?
    
    
    os_process* proc = os_process_new();
    
    os_process_delete(proc);
    
    //start build process
    //load library script
    //load pkgdef
    //load handle script
    
    //build application should return 0 when successful then the pkgbuild file must exist
    //return result? read result file? pkgbuild links to packages created?

}