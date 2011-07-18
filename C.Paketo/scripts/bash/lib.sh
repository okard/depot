############################
# Build Library Script
# Author: okard
# License: GPLv3
############################


# For beatiful output define colors:
ColorReset='\e[0m'      # Text Reset
Black='\e[0;30m'        # Black
Red='\e[0;31m'          # Red
Green='\e[0;32m'        # Green
Yellow='\e[0;33m'       # Yellow
Blue='\e[0;34m'         # Blue
Purple='\e[0;35m'       # Purple
Cyan='\e[0;36m'         # Cyan
White='\e[0;37m'        # White

############################
## Util Functions

function_exists()
{
    type -t $1 | grep -q "function"
}

############################
#Define Default Values

srcdir="src"
pkgdir="pkg"


############################
# Write pkgdb
write_pkgdb()
{
    echo -e "[${White}INFO${ColorReset}] Write pkgdb ..."
}

############################
# Write pkgbuild
write_pkgbuild()
{
    #write db before
    write_pkgdb

    echo -e "[${White}INFO${ColorReset}] Write pkgbuild ..."

    #support for splitted packages
    #write json pkgdb file tp pkgdir
    #write pkgbuild file dirs to package 
}

#dummy functions
pre_build() { sleep 0; }
build() { sleep 0; }
post_build() { sleep 0; }
package() { sleep 0; }
clean() { sleep 0; }
