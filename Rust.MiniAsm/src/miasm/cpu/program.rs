

use cpu::instruction::{Instr};

use std::collections::{HashMap};


pub struct Program
{
	data: Vec<u8>,
	code: Vec<Instr>,
	
	code_labels: HashMap<String, uint>, //&str without lifetime?
	data_map: HashMap<String, uint>,
}


impl Program 
{
	pub fn new() -> Program
	{
		Program {
			data: Vec::new(),
			code: Vec::new(),
			code_labels: HashMap::new(),
			data_map: HashMap::new()
		}
	}
	
	
}
