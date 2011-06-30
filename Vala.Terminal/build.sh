#!/usr/bin/env bash

valac --vapidir=. --pkg gtk+-3.0 --pkg vte3 -X -lvte2_90 -g -o vaterm src/TerminalApplication.vala src/TerminalWindow.vala 

