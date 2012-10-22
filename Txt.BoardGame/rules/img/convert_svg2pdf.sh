#!/usr/bin/env bash


mkdir -v -p ../generated/simple

for f in *.svg; do 
    echo "Create pdf for $f ..."; 
    
    #todo rename to ../generated/simple/

    inkscape -z -f $f -D --export-dpi=300 --export-pdf ../generated/simple/${f%.svg}.pdf
done