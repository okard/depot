#!/usr/bin/env bash

valac --pkg gtk+-3.0 \
--vapidir=. --pkg poppler-glib3 --Xcc=-lpoppler-glib \
src/*.vala \
-o pdfpres2