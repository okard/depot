
//use std::collections::{ Deque};

use io::{SourceInput};
use syntax::lexer::{self, Lexer, Token, TokenKind};
use ast::node::{self, Node};

pub struct Parser<'a>
{
	lexer: Lexer<'a>,
	tok_pos: usize
	//cur token ref?
}

impl<'a> Parser<'a>
{
	pub fn new<'b>(code_source: & 'b mut SourceInput) -> Parser<'b>
	{
		Parser { lexer: Lexer::new(code_source), tok_pos: 0 }
	}
	
	//-----------------------------
	
	pub fn parse(&mut self) -> Node
	{
		//lex one line and generate tokens
		self.lexer.tokenize();
		
		
		let mut list = Box::new(Vec::new());
		//generate a List and 
		while self.lexer.tokens.len() > 0
		{
			list.push(self.parse_command());
		}
		
		return Node::List(list);
	}
	
	/**
	* Parse a command
	*/
	fn parse_command(&mut self) -> Node
	{
		Node::Nothing
	}
	
	/**
	* Parse an expression
	*/
	fn parse_expression(&mut self) -> Node
	{
		self.next_token();
		//precedence climbing
		panic!();
	}

	/**
	* def <name> : <type> {} or = <expr>
	*/
	fn parse_def(&mut self) -> Node
	{
		//cur token = KwDef
		assert!(self.cur_kind() == TokenKind::KwDef);
		
		//let name = box self.cur_string();
		
		//skip :
		
		//parse type
		
		//match type
		//parse_function(name: Box<String>);
		//parse_var(name: Box<String>);
		//parse_object(name: Box<String>);
		
		panic!();
	}

	//merge_token_until_whitespace?
	
	//------------------------------------------------------------------
	
	fn cur_kind(&self) -> lexer::TokenKind
	{
		if self.lexer.tokens.len() > 0 {
			self.lexer.tokens.get(self.tok_pos).unwrap().kind
		}
		else {
			TokenKind::Eof
		}
	}
	
	fn cur_string(&self) -> String
	{
		if self.lexer.tokens.len() > 0 {
			self.lexer.tokens.get(self.tok_pos).unwrap().s.clone()
		}
		else {
			panic!();
		}
	}
	
	fn token_left(&self) -> usize
	{
		self.lexer.tokens.len()
	}
	
	fn next_token(&mut self)
	{
		//pop front token?
		if self.lexer.tokens.len() > 0 {
			self.lexer.tokens.pop_front();
		}
	}
	
	fn next_tok_nws(&mut self)
	{
		while self.lexer.tokens.len() > 0
		&& self.cur_kind() == TokenKind::Whitespace  {
			self.next_token();
		}
	}
}








#[test]
fn parser_test()
{
	use std::io;
	use std::vec;
	use lexer::Lexer;
	
	let test_string = String::from_str("ls -alh .");
	let mut reader = io::MemReader::new(test_string.into_bytes());
	let mut lexer = Lexer::new(&mut reader as &mut Buffer);
	let mut parser = Parser::new(&mut lexer);
	let ast_tree = parser.parse();
	
	
	
	//command
	//def func
	//def ...
	//let
	//expr
	
	// test stuff with new line? -> requires multiple tokenize calls
}
