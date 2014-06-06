
#![crate_id = "libshellng#0.1"]
#![crate_type = "lib"]

#![feature(globs)]

extern crate collections;
extern crate debug;

pub mod helper;

pub mod lexer;	//lexer

pub mod ast; // ast
pub mod parse;	//parser

pub mod exec;


//exec / interpreter?

pub mod shell; //main shell module?