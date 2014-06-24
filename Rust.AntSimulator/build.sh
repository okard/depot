#!/usr/bin/env bash


rustc -g -L . --crate-type=lib src/antcore/lib.rs 
rustc -g -L . -o shellng src/antsim/main.rs
