#!/usr/bin/env bash


# Generate the Token Library
./gentokensvg.py lib tokendb.txt generated/tokenlib.svg

echo

# Generate the overview sheet
./gentokensvg.py ov tokendb.txt tokenlib.svg generated/overview{0}.svg
