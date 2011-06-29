#!/usr/bin/env bash

valac --vapidir=. --pkg gtk+-3.0 --pkg vte3 -g -o vaterm src/main.vala -X -lvte2_90

