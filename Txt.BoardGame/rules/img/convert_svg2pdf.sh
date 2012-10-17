#!/usr/bin/env bash


for f in *.svg; do 
    echo "Create pdf for $f ..."; 
    
    inkscape -z -f $f -D --export-dpi=300 --export-pdf ../pdf/${f%.svg}.pdf
done