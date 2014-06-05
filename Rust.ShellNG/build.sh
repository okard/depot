#!/usr/bin/env bash


rustc -g --crate-type=lib src/libshellng/lib.rs 
rustc -g -L . -o shellng src/shellng/main.rs
