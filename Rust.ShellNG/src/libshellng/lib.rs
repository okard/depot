
#![crate_id = "libshellng#0.1"]
#![crate_type = "lib"]

#![feature(globs)]
//#![feature(struct_variant)] 

extern crate collections;
extern crate debug;

pub mod helper;

pub mod lexer;	// lexer

pub mod ast; // ast
pub mod parse;	// parser

pub mod visitor; // ast visitor
pub mod exec;	  // interpreter


//exec / interpreter?

pub mod shell; //main shell module?
