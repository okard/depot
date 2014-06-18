
use ast;
use ast::{Node};
use visitor::{Visitor};
use shell::ShellContext;

use std::io;

enum Value
{
	//string
	//number
	//function
	//map
	
	//Node?
}

//Context { values :  map<string, Node> }

struct Interpreter;

//implement visitor

impl Visitor for Interpreter
{
 	fn visit_list(&mut self, list: Box<Vec<Node>>) -> Node
 	{
		let mut merged = box String::new();
		 
		for item in list.move_iter() {
			let item = self.dispatch(item);
			
			match item {
				ast::StringLiteral(value) => { merged = box merged.append(value.as_slice()); }
				ast::Nothing => {}
				_ => { fail!() }
			}
		}
		
		//merge to a big string literal?
		ast::StringLiteral(merged)
	}
	
	fn visit_command(&mut self, command: Box<ast::Command_> ) -> Node
	{
		//execute command:
		let exe = self.dispatch(command.exe);;
		//validate args?
		
		let mut com : Option<io::Command> = None;
		match exe 
		{
			ast::StringLiteral(box exename) => { 
				//todo check for internal commands here?
				com = Some(io::Command::new(exename));   
			} 
			_ => {fail!();}
		}
		
		//go through arguments
		for arg in command.args.move_iter() {
			let arg = self.dispatch(arg);
			
			match arg {
				ast::StringLiteral(box argu) => { com.get_mut_ref().arg(argu); }
				_ => {fail!();}
			}
			
		}
		
		//set same stdout?
		com.get_mut_ref().stdout(::std::io::process::InheritFd(::libc::STDOUT_FILENO));
		
		//check for pipes and so 
		
		//configure stdin, stdout, stderr
		//configure env, cwd
		
		
		//println!("spawn: {}", com.get_ref());
		
		//spawn 
		let result = com.get_mut_ref().spawn();
		
		if result.is_err() {
			println!("Can't execute {} because {}", com.get_mut_ref(), result.err().get_ref());
		}
		
		ast::Nothing
	}
	
	fn visit_strlit(&mut self, value : Box<String>) -> Node
	{
		ast::StringLiteral(value)
	}
	
	fn visit_varlit(&mut self, value : Box<String>) -> Node
	{
		//take a lookup in ctx.symbol_table with key value 
		ast::VarLiteral(value)
	}
}

//execute ast	
	
pub fn exec(_ : &mut ShellContext, node: ast::Node)
{
	let mut ip = Interpreter; //::new(state);
	ip.dispatch(node);
	
	//return error list?
}


//impl the trait 


