
#![crate_id = "libshellng#0.1"]
#![crate_type = "lib"]

#![feature(globs)]
//#![feature(struct_variant)] 

#![allow(dead_code)]

extern crate collections;
extern crate debug;
extern crate rustnoise;

pub mod helper;

pub mod lexer;	// lexer

pub mod ast; // ast
pub mod parse;	// parser

pub mod visitor; // ast visitor
pub mod exec;	  // interpreter


//exec / interpreter?

pub mod shell; //main shell module?
