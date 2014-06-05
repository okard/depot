
use collections::deque::{Deque};

use lexer::{Token, Lexer};
use ast;

pub fn parse(lex: &mut Lexer) -> ast::AstNode
{
	//parse command
	lex.tokenize();
	
	while lex.tokens.len() > 0
	{
		parse_command(lex);
	}
	
	return ast::Empty;
}


fn parse_command(lex: &mut Lexer)
{
	let tok = (&mut lex.tokens as &mut Deque<Token>).pop_front();
	//if keyword parse keyword
	
}


fn parse_expression()
{
	
}


fn parse_def()
{
	
}
