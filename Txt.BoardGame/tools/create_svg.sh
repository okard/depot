#!/usr/bin/env bash

./gentokensvg.py lib tokendb.txt tokenlib.svg
./gentokensvg.py ov tokendb.txt tokenlib.svg overview.svg


# for future extension
# inkscape -z -f overview_test.svg --export-dpi=300 --export-pdf overview_test_2.pdf
