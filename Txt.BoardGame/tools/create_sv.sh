#!/usr/bin/env bash


# create single view svgs
mkdir -v -p generated/token
./gentokensvg.py sv tokendb.txt "generated/token/token_{0}_{1}_{2}.svg"

# convert each single view svg to pdf
for f in generated/token/token_*.svg; do 
    echo "Create pdf for $f ..."; 

    # rules/generated/token/
    inkscape -z -f $f -D --export-dpi=300 --export-pdf ../rules/${f%.svg}.pdf
done


# create tex 

echo "Create tex list"

file="../rules/generated/tokendb.tex"
echo "%generated" > $file
echo "\\begin{longtable}{lllll}" >> $file
echo "\\hline" >> $file 
echo "Vorderseite \\& Rückseite & Wert & Kürzel & Beschreibung \\\\ \\hline" >> $file 

for f in ../rules/generated/token/token_*.pdf; do 
    #\includegraphics[scale=3]{generated/token/token_120010011_220010023.pdf} & • & • \\
    value=$(basename "$f")
    value=(${value//_/ })
 
    echo -n "\includegraphics[scale=3]{" >> $file
    echo -n ${f:9} >> $file
    echo "} & ${value[1]} &  &  \\\\ \\hline" >> $file
done

echo "\\hline" >> $file
echo "\\end{longtable}" >> $file

