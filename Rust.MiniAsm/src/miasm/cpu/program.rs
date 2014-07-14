

use cpu::instruction::{Instr};

use std::collections::{HashMap};


pub struct Program
{
	pub data: Vec<u8>,
	pub code: Vec<Instr>,
	
	pub code_labels: HashMap<String, uint>, //&str without lifetime?
	pub data_map: HashMap<String, uint>,
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
	
	pub fn add_data(&mut self, name: &String, data: &[u8])
	{
		println!("add_data: {}:{}", name, data);
	}
	
	
	pub fn add_label(&mut self, name: &String)
	{
		//use current position
		println!("add_label: {}", name);
	}
	
	pub fn add_instr(&mut self, instr: Instr)
	{
		self.code.push(instr);
	}

	pub fn dump(&self)
	{
	}
}
