#!/usr/bin/env bash


# create single view svgs
mkdir -v -p generated/token
./gentokensvg.py sv tokendb.txt "generated/token/token_{0}_{1}.svg"

# convert each single view svg to pdf
for f in generated/token/token_*.svg; do 
    echo "Create pdf for $f ..."; 

    # rules/generated/token/
    inkscape -z -f $f -D --export-dpi=300 --export-pdf ../rules/${f%.svg}.pdf
done


# create tex 

echo "Create tex list"
echo "%generated" > ../rules/generated/tokendb.tex
for f in ../rules/generated/token/token_*.pdf; do 

    #\includegraphics[scale=3]{generated/token/token_120010011_220010023.pdf} & • & • \\ 
    echo -n "\includegraphics[scale=3]{" >> ../rules/generated/tokendb.tex
    echo -n ${f:9} >> ../rules/generated/tokendb.tex
    echo "} & • & • \\\\" >> ../rules/generated/tokendb.tex
done

