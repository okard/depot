#!/usr/bin/env bash


# Generate the Token Library
./gentokensvg.py lib tokendb.txt generated/tokendb.svg

echo

# Generate the overview sheet
# tokenlib.svg is only used as filename so no directory needed
./gentokensvg.py ov tokendb.txt tokendb.svg generated/overview{0}.svg
