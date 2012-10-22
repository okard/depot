#!/usr/bin/env bash


#build images
pushd img
./convert_svg2pdf.sh
popd

# Run Scripts for tokendb creation here

pushd ../tools
./create_sv.sh
popd



# Build Twice for Index
pdflatex rules.de.tex
pdflatex rules.de.tex