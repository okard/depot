
#![feature(globs)]
#![feature(struct_variant)] 

#![allow(dead_code)]

extern crate libc;
extern crate collections;
//extern crate debug;
extern crate rustnoise;


pub mod io;
pub mod helper;

//syntax module
pub mod syntax
{
	pub mod lexer;
	pub mod parse;
}

//syntax tree module
pub mod ast {
	pub mod node;
	pub mod visitor;
}

//execution module (interpreter, contexts, ...)
pub mod vm {
	pub mod exec;	  // interpreter
}


pub mod shell; //main shell module?
