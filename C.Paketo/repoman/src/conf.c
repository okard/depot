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
#include "conf.h"

#include <stdlib.h>

/**
* Open configuration
*/
rm_config* rm_open_config(const char* path)
{
    rm_config* rmc = malloc(sizeof(rm_config));
    
    //rmc->node = yajl_tree_parse((const char *) fileData, errbuf, sizeof(errbuf));
    //file buffer = size of file
    
    return rmc;
}

/**
* Close configuration
*/
void rm_close_config(rm_config* conf)
{
    free(conf);
    conf = 0;
}

/**
* Set up build action from config
*/
void rm_prepare_build(rm_config* conf, pkto_action_build* ba)
{
    //yajl_val v = yajl_tree_get(node, path, yajl_t_string);
    //ba.bash_lib_path
    //ba.bash_post_path
}