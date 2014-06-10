
use ast;
use shell::ShellContext;



trait AstVisitor 
{
	fn dispatch(&self);
	//dispatch
	
	//visit
}


//execute ast

	//exec(shell_state, ast_tree);
	
	
pub fn exec(shstate : &mut ShellContext, node: &Box<ast::AstNode>)
{
	//let mut ip = Interpreter::new(state);
	//ip.interpret(node);
	
}


//impl the trait 


