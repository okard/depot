#!/usr/bin/env bash


./merge_svg.py

convert -units PixelsPerInch -density 300 overview_merged.svg overview.pdf

#inkscape -z -f overview_merged.svg--export-dpi=300 --export-pdf overview.pdf