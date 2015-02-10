
use ast::node::{self, Node};
use ast::visitor::{Visitor};
use shell::ShellContext;

use std::old_io;

enum Value
{
	//string
	//number
	//function
	//map
	
	//Node?
}

//Context { values :  map<string, Node> }

struct Interpreter; //context stack

//implement visitor

impl Visitor for Interpreter
{
 	fn visit_list(&mut self, list: Box<Vec<Node>>) -> Node
 	{
		Node::Nothing
	}
	
	fn visit_command(&mut self, node: &Node ) -> Node
	{
		Node::Nothing
	}
	
	fn visit_strlit(&mut self, value : Box<String>) -> Node
	{
		Node::StringLiteral(value)
	}
	
	fn visit_varlit(&mut self, value : Box<String>) -> Node
	{
		//take a lookup in ctx.symbol_table with key value 
		Node::VarLiteral(value)
	}
}

//execute ast	
	
pub fn exec(_ : &mut ShellContext, node: Node)
{
	let mut ip = Interpreter; //::new(state);
	ip.dispatch(node);
	
	//return error list?
}


//impl the trait 


