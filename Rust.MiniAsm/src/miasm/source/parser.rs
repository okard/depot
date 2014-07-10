
use cpu::program::{Program};

use lex = source::lexer;

use io = std::io;


pub fn parse(path: &Path) -> Program //->Result
{
	let mut program = Program::new();
	
	//read lines?
	let mut file = io::BufferedReader::new(io::File::open(path));
	for line in file.lines() 
	{
		//line error
		if line.is_err() {
			return program;
		}
		
		let mut toks = lex::lex(line.unwrap().as_slice());
		toks.push(lex::Newline);
		parse_toks(&mut program, &toks);
		//each line is something
	}
	
	program
}


fn parse_toks(program: &mut Program, toks: &Vec<lex::Token>) 
{
	//Section
	//Label
	//
	
}

