
#![allow(dead_code)]
#![feature(macro_rules)] 

use std::os;
use std::path::{Path};

pub mod cpu {
	pub mod register;
	pub mod instruction;
	pub mod program;
	pub mod cpu;
}

pub mod source {
	pub mod lexer;
	pub mod parser;
}



fn main()
{
	let args = os::args();
	
	if args.len() != 2 {
		println!("Invalid arguments, one source file required");
		return;
	}
	
	let src_path = Path::new(args.get(1).as_slice());
	
	if !src_path.exists() {
		println!("The given source file doesn't exist: {}", src_path.as_str().unwrap());
		return;
	}
	
	
	let prog = source::parser::parse(&src_path);
	
	//source_path -> Program
	
	
	//start cpu/cli
}
