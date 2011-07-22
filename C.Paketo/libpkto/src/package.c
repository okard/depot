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
#include <pkto/pkto.h>
#include <pkto/package.h>


/**
* Install a package
*/
void pkto_package_install(pkto_handle* handle)
{
    //check for conflicts
    //check dependencies
    //add to a queue
}

/**
* Remove a package
*/
void pkto_package_remove(pkto_handle* handle)
{
    //check for dependencies
}

/**
* Upgrade a package
*/
void pkto_package_upgrade(pkto_handle* handle)
{
    //old package information
    //compare?
}

/**
* Package Status
*/
void pkto_package_status(pkto_handle* handle)
{
    //package status
}