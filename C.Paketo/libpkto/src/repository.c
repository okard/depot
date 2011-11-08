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

#include <kclangc.h>

#include <pkto/handle.h>
#include <pkto/repository.h>


//pkto_repository

//open a repository
void pkto_repository_open(pkto_handle* handle)
{
}

//get a package from repository
void pkto_repository_package(pkto_handle* handle)
{
}

// synchronize repository
void pkto_repository_sync(pkto_handle* handle)
{
    //http get db file? diff ?
    //rsync sync files
    //detect packages to upgrade?
}

//open the db for repository (shared between repositories?)
void pkto_repository_db_open(pkto_handle* handle)
{
    //open repository cache?
}




//read package informations and so on

//read package information from pkgdb
//read package information from kyoto cabinet db? (is json stored?)
