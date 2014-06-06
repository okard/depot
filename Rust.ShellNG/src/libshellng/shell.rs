
use std::io;
use std::io::Buffer;
//use std::io::File;

//import lexer
use lexer::{Lexer};
use parse;

/*
* Shell State
*/
struct ShellState<'a>
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
		//parse a complete syntax tree:
		let ast_tree = parse::parse(&mut self.lexer);
		
		//execute the tree
		// exec(state, tree);
		
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
