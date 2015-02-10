
//use std::io::File;

use io;

//import lexer
use syntax::lexer::{Lexer};
use syntax:: parse::{Parser};

use vm::exec;

pub struct ShellContext; //ContextTable
						  // RuntimeContext?
						  
						  


// a working struct is shellio/parse/lex/context 

//todo rename to Shell, ShellCore? ShellContext?
/*
* Shell State 
*/
pub struct ShellState<'a>
{
	parser: Parser<'a>,
	//parser?
	
	
	//reader
	
	//lexer_stdin
	//lexer_file
	
	//shellio
	
	//current scope/context/etc
	
	//cwd
	//env
	
	//current processes
	//shellcontext
}

impl<'a> ShellState<'a>
{	
	fn new<'b>(shell_input: & 'b mut io::SourceInput) -> ShellState<'b>
	{
		 ShellState { 
						parser: Parser::new(shell_input)
				}
	}
	
	
	fn run_line(&mut self) -> bool
	{
	
		//parse a complete syntax tree:
		let ast_tree = self.parser.parse();
		
		//println!("{}", ast_tree);
		
		let mut shctx = ShellContext;
		//execute the tree
		exec::exec(&mut shctx, ast_tree);
		
		
		true
	}
}


fn do_line<'a>(ss : & 'a mut ShellState<'a>)
{
	ss.run_line();
}

pub fn run()
{
	/*
	//stdin implementation:
	let mut std_input = io::stdin();
	let mut shell_input = input::ShellBufferInput::new(&mut std_input as &mut Buffer);
	let shell_reader = &mut shell_input as &mut input::ShellInput;
	*/
	
	//create a linenoise input
	let mut shell_input = io::linenoise::ShellNoiseInput::new("shellng > ");
	
	//create shell state/context
	let mut state = ShellState::new(&mut shell_input);
	
	//event loop
	loop  
	{
		//do_line(&mut state);
	}
}
