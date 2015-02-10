
use ast::node::{self, Node};


pub trait Visitor
{
	fn visit_list(&mut self, list: Box<Vec<Node>>) -> Node;
	fn visit_command(&mut self, node: &Node) -> Node;
	fn visit_strlit(&mut self, value : Box<String>) -> Node;
	fn visit_varlit(&mut self, value : Box<String>) -> Node;
	
	
	fn dispatch(&mut self, n: Node) -> Node
	{
		match n {
		Node::List(list) => {return self.visit_list(list); }
		Node::StringLiteral(strlit) =>  {return self.visit_strlit(strlit); }
		Node::VarLiteral(varlit) =>  {return self.visit_varlit(varlit); }
		
		_ => { panic!(); }
		}
	}
}
