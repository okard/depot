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
    
    actions
*/
#pragma once
#ifndef __LIBPKTO_ACTION_H__
#define __LIBPKTO_ACTION_H__

#include <pkto/handle.h>

/**
* \defgroup Action Paketo Actions
* @{
*/

/**
* Action State
*/
typedef enum pkto_action_state
{
    PKTO_ACTION_STATE_NONE,
    PKTO_ACTION_STATE_FAILED,
    PKTO_ACTION_STATE_SUCCESSFUL 
    
} pkto_action_state;

/**
* Build Action
*/
typedef struct pkto_action_build
{
    ///pkto handle
    pkto_handle* handle;
    /// State of these Action
    pkto_action_state state;
    
    /// Parameter Package Def Path
    char* path;
    
    //vfs

    /// Parameter Bash Build Library Path
    char* bash_lib_path;
    
    /// Parameter Bash Build Post Script
    char* bash_post_path;
    
    //result?
    
} pkto_action_build;


/**
* Package Action
*/
typedef struct pkto_action_package
{
    ///pkto handle
    pkto_handle* handle;
    /// State of these Action
    pkto_action_state state;
    
    //package
    //action remove/install/upgrade (user/dep)

    //config
    //target directory (e.g. root /)
    char* root_dir;
    //vfs_dir root
    
    //result?
    
} pkto_action_package;



/**
* Build a package
* TODO build results?
* TODO Build Action? as structure?
*/
void pkto_build(pkto_action_build* build_action);


/** }@ */

#endif 