#!/usr/bin/env bash


#this script creates overview pdfs

# Generate the Token Library
echo 'Generate Token Library'
./genLibrary.py tokendb.txt generated/tokendb.svg


# Generate the overview sheet
# tokenlib.svg is only used as filename so no directory needed
echo 'Generate Token Overviews'
./gentokensvg.py tokendb.txt tokendb.svg generated/overview{0}.svg

#Template: overview%1.svg files

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
