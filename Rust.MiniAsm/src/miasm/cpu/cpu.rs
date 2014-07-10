
use cpu::register::{Register};



struct CPU
{
	memory: Vec<u8>, 	//the memory aka ram
	reg: Vec<u32>, 		//register values (use Register No as index)
}


//basic mode:

//reset
//run_program
//run_step


//complete in mem mode:

//load_program -> maps program into memory
//run
//run_complete

