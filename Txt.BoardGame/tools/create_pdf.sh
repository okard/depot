#!/usr/bin/env bash


# overview%1.svg files


# create merged svg files
for f in generated/overview[0-9].svg; do 
    echo "Create merged svg for $f ..."; 
    ./merge_svg.py $f generated/tokendb.svg generated/merged_$(basename "$f")
done

# create pdfs for the merged files
for f in generated/merged_overview[0-9].svg; do 
    echo "Create pdf for $f ..."; 
    convert -units PixelsPerInch -density 300 $f generated/$(basename "$f").pdf
done


#convert -units PixelsPerInch -density 300 overview_merged.svg overview.pdf

#inkscape -z -f overview_merged.svg--export-dpi=300 --export-pdf overview.pdf