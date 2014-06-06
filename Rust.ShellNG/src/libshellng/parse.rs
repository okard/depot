
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
	
	//parse <expr> only when PlaceId is found
		// ls -l $myvar.get
	
	//look for special kw
		//def, if, match, ...?
	
	//match
	
	//if keyword parse keyword
}


fn parse_expression()
{
	//precedence climbing
}

// def <name> : <type> {} or = <expr>
fn parse_def()
{
	
}

//token
//next_nowhitespace
//next
//merge_token_until_whitespace?
