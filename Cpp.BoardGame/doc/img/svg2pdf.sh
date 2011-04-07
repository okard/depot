#!/usr/bin/env bash

outname=${1//./_}     

inkscape -z -D --file=$1 --export-pdf="${outname}.pdf" 
