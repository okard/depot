#!/usr/bin/env bash


# Generate the Token Library
./gentokensvg.py lib tokendb.txt tokenlib.svg

# Generate the overview sheet
./gentokensvg.py ov tokendb.txt tokenlib.svg overview.svg
