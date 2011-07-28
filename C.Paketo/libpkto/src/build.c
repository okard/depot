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
#include <pkto/action.h>

#include <pkto/os.h>

#include <cpr/error.h>

#include <assert.h>

//For Debug
#include <stdio.h>

//libArchive
#include <archive.h> 

/**
* OS Process Error Handler
*/
static void os_process_error_handler(cpr_error* err)
{
    //pkto_handle_error((pkto_handle*)err->ctx, err->msg) 
    //error from pkto_handle in ctx
    fprintf(stderr, "Error from os_process: %s\n", err->msg);
}

/**
* Build a package
*/
void pkto_build(pkto_action_build* build_action)
{
    //check if action is valid
    assert(build_action != 0);
    //assert(build_action.handle != 0);
    //assert(build_action.bash_lib_path != 0);
    //assert(build_action.bash_post_path != 0);
    
    
    //opendir
    //look for pkgdef
    //open path + pkgdef
    
    //signed pkgdef ?
    //requires pkgdef
    
    
    //line ending? map build tool? .sh = bash, .lua = lua and so on?
    //requires folder with pkgdef
    //test if folder is writeable?
    //build to temp if nota?
    
    
    os_process* proc = os_process_new();
    os_process_set_error_handler(proc, &os_process_error_handler, build_action->handle);
    
    //path of lib.sh and post.sh
    //bash -c ". lib.sh; . pkgdef; . post.sh;"
    //sprintf
    static const char* cmdLine = ". %s; . %s; . %s;";
    //command str sprintf(str, ". %s; . %s; . %s;", libsh, pkgdef, postsh); 
    //start a bash process
    //load . lib.sh
    //load . pkgdef
    //load . post.sh to create package
    // create right string with full pathes
    //os_process_start(proc, "/usr/bin/bash", "/usr/bin/bash", "-c", "", NULL);
    
    const char* args[] = {"/bin/ls", "-alh", (char *)0 };
    os_process_start(proc, args[0], args);
    os_process_wait(proc);
    
    os_process_delete(proc);
    
    //start build process
    //load library script
    //load pkgdef
    //load handle script
    
    //build application should return 0 when successful then the pkgbuild file must exist
    //return result? read result file? pkgbuild links to packages created?
    
    //get dir with package informationen create archive here
}


/**
* Creates a archive from directory
*/
void pkto_write_archive_from_dir(char* dir, char* archive_file)
{
    /*
     
    struct archive *a;
    struct archive_entry *entry;
    struct stat st;
    char buff[8192];
    int len;
    int fd;

    a = archive_write_new();
    archive_write_set_compression_gzip(a);
    archive_write_set_format_pax_restricted(a); // Note 1
    archive_write_open_filename(a, outname, 10240);
    while (*filename) 
    {
      stat(*filename, &st);
      entry = archive_entry_new(); // Note 2
      archive_entry_set_pathname(entry, *filename);
      archive_entry_set_size(entry, st.st_size); // Note 3
      archive_entry_set_filetype(entry, AE_IFREG);
      archive_entry_set_perm(entry, 0644);
      archive_write_header(a, entry);
      fd = open(*filename, O_RDONLY);
      len = read(fd, buff, sizeof(buff));
      while ( len > 0 ) 
      {
          archive_write_data(a, buff, len);
          len = read(fd, buff, sizeof(buff));
      }
      close(fd);
      archive_entry_free(entry);
      filename++;
    }
    archive_write_close(a); // Note 4
    archive_write_finish(a); // Note 5

    */
}