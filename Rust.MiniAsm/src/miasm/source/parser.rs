
use cpu::program::{Program};
use instr = cpu::instruction;

use lex = source::lexer;

use io = std::io;

struct Parser
{
	program: Program
	//safe sections?
}

impl Parser
{
	//get the token from one line so one instruction
	fn parse_toks(&mut self, toks: &Vec<lex::Token>) 
	{
		if toks.len() <= 0 {
			return;
		}
		
		match toks.get(0) 
		{
			&lex::Newline => { return; }
			
			&lex::Section(ref s) => { println!("Ignore Section: {}", s);  }
			
			//syntax: $ident : "data" (allow % )
			&lex::DataAddress(ref name) => {
				
				if toks.get(1) != &lex::Colon {
					println!("missing : after ${}", name);
				}

				match toks.get(2) 
				{
					&lex::StringLiteral(ref data) => {
							self.program.add_data(*name, data.as_bytes());
						}
					_ => { println!("invalid token after ${}:", name); }
				}
			}
			
			&lex::Label(ref name) => { self.program.add_label(*name); }
			&lex::Ident(_) => {self.parse_instruction(toks); }
			&lex::Macro(_) => {self.parse_instruction(toks); }
			
			
			//macro
			//ident
			
			//fails
			_ => { println!("Invalid token: {}", toks.get(0)); }
		}
	}
	
	fn parse_instruction(&mut self, toks: &Vec<lex::Token>) 
	{
		match toks.get(0) 
		{
			//push
			&lex::Ident(ref name) if name == &box "push".to_string() => {
				
			}
			
			
			//mov R, R
			//mov R, C
			&lex::Ident(ref name) if name == &box "mov".to_string() => 
			{
				match (toks.get(1), toks.get(2), toks.get(3))
				{
					// mov R, R
					(&lex::RegIdent(reg1), &lex::Comma, &lex::RegIdent(reg2)) => 
					{ 
						let mut i : instr::Instr = 0;
						instr::set_instr(&mut i, instr::MOV_R_R, reg1, reg2); 
						self.program.add_instr(i);
					}
					
					// mov R, R
					(&lex::RegIdent(reg1), &lex::Comma, &lex::Constant(ref c)) => 
					{ 
						let mut i : instr::Instr = 0;
						instr::set_instr_r_c(&mut i, instr::MOV_R_C, reg1, Parser::const_value(c.as_slice())); 
						self.program.add_instr(i);
					}
					
					_ => { println!("Invalid mov instruction");}
				}
				
			}
			
			//add R, R
			&lex::Ident(ref name) if name == &box "add".to_string() => 
			{
				match (toks.get(1), toks.get(2), toks.get(3))
				{
					// add R, R
					(&lex::RegIdent(reg1), &lex::Comma, &lex::RegIdent(reg2)) => 
					{ 
						let mut i : instr::Instr = 0;
						instr::set_instr(&mut i, instr::ADD_R_R, reg1, reg2); 
						self.program.add_instr(i);
					}
					_ => { println!("Invalid mov instruction");}
				}
			}
			
			//cmp R, R
			//cmp R, C
			&lex::Ident(ref name) if name == &box "cmp".to_string() => 
			{
				match (toks.get(1), toks.get(2), toks.get(3))
				{
					// cmp R, R
					(&lex::RegIdent(reg1), &lex::Comma, &lex::RegIdent(reg2)) => 
					{ 
						let mut i : instr::Instr = 0;
						instr::set_instr(&mut i, instr::CMP_R_R, reg1, reg2); 
						self.program.add_instr(i);
					}
					
					_ => { println!("Invalid cmp instruction");}
				}
				
			}
			
			
			
			_ => { println!("Invalid instruktion {}", toks.get(0));  }
		}
		
	}
	
	
	fn const_value(s : &str) -> u32
	{
		let value : Option<u32> = from_str(s);
		value.unwrap()
	}
}



pub fn parse(path: &Path) -> Program //->Result
{
	let mut parser = Parser {
		program: Program::new()
	};
	
	
	
	//read lines?
	let mut file = io::BufferedReader::new(io::File::open(path));
	for line in file.lines() 
	{
		//line error
		if line.is_err() {
			return parser.program;
		}
		
		let mut toks = lex::lex(line.unwrap().as_slice());
		toks.push(lex::Newline);
		parser.parse_toks(&toks);
	}
	
	parser.program
}



