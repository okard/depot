
use std::collections::{ Deque};

use lexer;
use ast;
use ast::{Node};

pub struct Parser<'a>
{
	lexer:  & 'a mut lexer::Lexer<'a>,
	tok_pos: uint
	//cur token ref?
}

impl<'a> Parser<'a>
{
	pub fn new(lex: & 'a mut lexer::Lexer) -> Parser<'a>
	{
		Parser { lexer: lex, tok_pos: 0 }
	}
	
	//-----------------------------
	
	pub fn parse(&mut self) -> Node
	{
		//lex one line and generate tokens
		self.lexer.tokenize();
		
		
		let mut list = box Vec::new();
		//generate a List and 
		while self.lexer.tokens.len() > 0
		{
			list.push(self.parse_command());
		}
		
		return ast::List(list);
	}
	
	/**
	* Parse a command
	*/
	fn parse_command(&mut self) -> Node
	{
		//this is called when lexer has lexed one line?
		
		//keywords
		if self.cur_kind() == lexer::KwDef {
			return self.parse_def();
		}
		
		//keywords: let, if, etc
		
		
		//otherwise it is a command:
		//list for the exe expression (is a list of nodes)
		let mut exe_list = box Vec::new();
		
		//first parse exe name
		loop 
		{
			match self.cur_kind()
			{
				//all stuff other then PlaceId or Whitespace are added to exe name
				lexer::PlaceId => { exe_list.push(self.parse_expression()); /* except only non whitespace expr here? */ }
				lexer::Whitespace => {}
				lexer::Eof => {}
				_ => { exe_list.push(ast::StringLiteral(box self.cur_string())); self.next_token(); }
			}
			
			//handle whitespace and eof
			match self.cur_kind()
			{
				lexer::Whitespace => { self.next_token(); break; }
				lexer::Eof => { break; }
				_ => {}
			}
		}
		
		//list of all arguments (each argument is also a list)
		let mut args_list = Vec::new();
		
		//parse arguments until no tokens anymore (aka line end)
		while self.token_left() > 0
		{
			let mut arg_list = box Vec::new();
			
			//todo parse special shell stuff pipes and so on
			
			//parse a single argument until first whitespace
			loop 
			{
				match self.cur_kind()
				{
					lexer::PlaceId => { arg_list.push(self.parse_expression()); }
					lexer::Whitespace => {}
					lexer::Eof => {}
					_ => {arg_list.push(ast::StringLiteral(box self.cur_string())); self.next_token();}
				}
				
				//handle whitespace and eof
				match self.cur_kind()
				{
					lexer::Whitespace => { self.next_token(); break; }
					lexer::Eof => { break; }
					_ => {}
				}
			}
			
			//create the argument ast node and add it to command;
			args_list.push(ast::List(arg_list));
		}
	
		
		return ast::Command( box ast::Command_ { 	exe: ast::List(exe_list), 
													args: args_list
		});
	}
	
	/**
	* Parse an expression
	*/
	fn parse_expression(&mut self) -> Node
	{
		self.next_token();
		//precedence climbing
		fail!();
	}

	/**
	* def <name> : <type> {} or = <expr>
	*/
	fn parse_def(&mut self) -> Node
	{
		//cur token = KwDef
		assert!(self.cur_kind() == lexer::KwDef);
		
		//let name = box self.cur_string();
		
		//skip :
		
		//parse type
		
		//match type
		//parse_function(name: Box<String>);
		//parse_var(name: Box<String>);
		//parse_object(name: Box<String>);
		
		fail!();
	}

	//merge_token_until_whitespace?
	
	//------------------------------------------------------------------
	
	fn cur_kind(&self) -> lexer::TokenKind
	{
		if self.lexer.tokens.len() > 0 {
			self.lexer.tokens.get(self.tok_pos).kind
		}
		else {
			lexer::Eof
		}
	}
	
	fn cur_string(&self) -> String
	{
		if self.lexer.tokens.len() > 0 {
			self.lexer.tokens.get(self.tok_pos).s.clone()
		}
		else {
			fail!();
		}
	}
	
	fn token_left(&self) -> uint
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
		&& self.cur_kind() == lexer::Whitespace  {
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
