
use ast;
use ast::{Node};


pub trait Visitor
{
	fn visit_list(&mut self, list: Box<Vec<Node>>) -> Node;
	fn visit_command(&mut self, command: Box<ast::Command_> ) -> Node;
	
	fn dispatch(&mut self, n: Node) -> Node
	{
		match n {
		ast::Command(command) => {return self.visit_command(command); }
		ast::List(list) => {return self.visit_list(list); }
		_ => { fail!(); }
		}
	}
}
