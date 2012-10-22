#!/usr/bin/env bash


# create single view svgs
./gentokensvg.py sv tokendb.txt "generated/token_{0}_{1}.svg"

# convert each single view svg to pdf
for f in generated/token_*.svg; do 
    echo "Create pdf for $f ..."; 

    # rules/generated/token/
    inkscape -z -f $f -D --export-dpi=300 --export-pdf ${f%.svg}.pdf
done

