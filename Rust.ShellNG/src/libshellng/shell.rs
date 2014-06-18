
//use std::io::File;

use input;

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
	//shellcontext
}

impl<'a> ShellState<'a>
{	
	fn step(&mut self) -> bool
	{
		let mut parser = Parser::new(&mut self.lexer);
		//parse a complete syntax tree:
		let ast_tree = parser.parse();
		
		println!("{}", ast_tree);
		
		let mut shctx = ShellContext;
		//execute the tree
		exec::exec(&mut shctx, ast_tree);
		
		true
	}
}


pub fn run()
{
	/*
	//stdin implementation:
	let mut std_input = io::stdin();
	let mut shell_input = input::ShellBufferInput::new(&mut std_input as &mut Buffer);
	let shell_reader = &mut shell_input as &mut input::ShellInput;
	*/
	
	let mut shell_input = input::ShellNoiseInput { prompt: "shellng > ".to_string() };
	
	//create shell state/context
	let mut state = ShellState { lexer: Lexer::new(&mut shell_input)
							     };
	
	//event loop
	loop 
	{
		if !state.step()
		{
			break;
		}
	}
}
