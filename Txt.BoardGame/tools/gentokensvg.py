#!/usr/bin/env python3

import sys
import re

      

        



    

#############################################################################
# Main Program 
#############################################################################

# command lib - create lib
# command ov - create overview sheet
# command sv - single view
# command com - command mode

        
if len(sys.argv) < 2:
    sys.exit("Usage: script lib/ov")     
   
    


# command mode
if sys.argv[1] == 'com':
    
    if len(sys.argv) < 4:
        sys.exit("Usage: script com CommandFile TokenLib.svg")
       
# Create single images for each token? or double images with front and backside?
# Create also latex db template

    
