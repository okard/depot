
#![crate_id = "libshellng#0.1"]
#![crate_type = "lib"]

extern crate debug;

pub mod lexer;	//lexer
pub mod parse;	//parser
pub mod ast; // ast

//exec / interpreter?

pub mod shell; //main shell module?
