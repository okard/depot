/*
    This file is part of repoman.

    repoman is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    repoman is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with repoman.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef __REPOMAN_CONFIG_H__
#define __REPOMAN_CONFIG_H__

#include <pkto/action.h>

#include <yajl/yajl_tree.h>

/**
* Repoman Configuration
*/
typedef struct rm_config
{
    yajl_val node;
    char* buffer;
    
} rm_config;

/**
* Open configuration
*/
rm_config* rm_open_config(const char* path);

/**
* Close configuration
*/
void rm_close_config(rm_config* conf);


/**
* Set up build action from config
*/
void rm_prepare_build(rm_config* conf, pkto_action_build* ba);


#endif