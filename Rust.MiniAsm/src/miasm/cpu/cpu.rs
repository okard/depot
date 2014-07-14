
use cpu::program::{Program};
use cpu::instruction::{Instr};
use instr = cpu::instruction;
use reg = cpu::register;



pub struct CPU
{
	memory: Vec<u8>, 	//the memory aka ram
	reg: Vec<u32>, 		//register values (use Register No as index)
}



impl CPU 
{
	pub fn new() -> CPU 
	{
		CPU {
			memory: Vec::with_capacity(1024), //1024 bytes memsize
			reg: Vec::with_capacity(10)
		}
	}
	
	pub fn run(&mut self, p : &Program)
	{
		self.reg.grow_set(reg::REG_A as uint, &0, 0);
		self.reg.grow_set(reg::REG_B as uint, &0, 0);
		self.reg.grow_set(reg::REG_C as uint, &0, 0);
		self.reg.grow_set(reg::REG_D as uint, &0, 0);
		self.reg.grow_set(reg::LOOP as uint, &0, 0);
		self.reg.grow_set(reg::CMP as uint, &0, 0);
		self.reg.grow_set(reg::PC as uint, &0, 0);
		self.reg.grow_set(reg::ST as uint, &0, 0);
		self.reg.grow_set(reg::FP as uint, &0, 0);
		
		//set pc to start code
		
		
		
		loop  {
			//get pc & instr
			let mut pc : uint = *self.reg.get(reg::PC as uint) as uint;
			let instr = p.code.get(pc);
			
			if pc < p.code.len() {
				break;
			}

			//set it already to the next
			pc += 1;
			*self.reg.get_mut(reg::PC as uint) = pc as u32;
				
			//run instruction
			self.run_instr(*instr);
		}
	}
	
	fn run_instr(&mut self, instr: Instr)
	{
		match instr::get_op(instr)
		{
			instr::MOV_R_C => {
				let reg_1 = instr::get_reg1(instr);
				
			}
			
			_ => { println!("not implemented opcode"); }
		}
	}
	
	pub fn dump(&self)
	{
		println!("REG_A [{}]", self.reg.get(reg::REG_A as uint));
		println!("REG_B [{}]", self.reg.get(reg::REG_B as uint));
		println!("REG_C [{}]", self.reg.get(reg::REG_C as uint));
		println!("REG_D [{}]", self.reg.get(reg::REG_D as uint));
	}
}



//basic mode:

//reset
//run_program
//run_step


//complete in mem mode:

//load_program -> maps program into memory
//run
//run_complete

