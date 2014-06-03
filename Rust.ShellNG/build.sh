#!/usr/bin/env bash


rustc --crate-type=lib src/libshellng/lib.rs 
rustc -L . -o shellng src/shellng/main.rs
