
use std::io;
use std::io::Buffer;
//use std::io::File;

//import lexer
use lexer::{Lexer};
use parse::{Parser};

use exec;

pub struct ShellContext;

/*
* Shell State
*/
pub struct ShellState<'a>
{
	lexer: Lexer<'a>
	//reader
	
	//lexer_stdin
	//lexer_file
	
	//current scope/context/etc
	
	//current processes
}

impl<'a> ShellState<'a>
{	
	fn step(&mut self) -> bool
	{
		let mut parser = Parser::new(&mut self.lexer);
		//parse a complete syntax tree:
		let ast_tree = parser.parse();
		
		let mut shctx = ShellContext;
		//execute the tree
		exec::exec(&mut shctx, &ast_tree);
		
		//prompt
		print!("shellng> ");
		
		true
	}
}


pub fn run()
{
	// run on stdin?
	let mut stdin = io::stdin();
	let reader = &mut stdin as &mut io::Buffer;
	
	//create shell state/context
	let mut state = ShellState { 
									lexer: Lexer::new(reader)
							     };
	
	//prompt
	print!("shellng> ");
	
	//event loop
	loop 
	{
		if !state.step()
		{
			break;
		}
	}
}
