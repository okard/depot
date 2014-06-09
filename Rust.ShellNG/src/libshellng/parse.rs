
use collections::deque::{Deque};

use lexer;
use ast;

pub fn parse(lex: &mut lexer::Lexer) -> ast::AstNode
{
	//parse command
	lex.tokenize();
	
	while lex.tokens.len() > 0
	{
		parse_command(lex);
	}
	
	return ast::Empty;
}


fn parse_command(lex: &mut lexer::Lexer)
{
	let tok_o = lex.tokens.pop_front();
	let tok_ref = tok_o.get_ref();
	
	if tok_ref.kind == lexer::PlaceId {
	}
	
	match tok_ref.kind
	{
		lexer::Id => {}
		_ => ()
	}
	
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

#[test]
fn parser_test()
{
	
}
