
use collections::deque::{Deque};

use lexer;
use ast;


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
	
	fn cur_kind(&self) -> lexer::TokenKind
	{
		self.lexer.tokens.get(self.tok_pos).kind
	}
	
	fn cur_string(&self) -> String
	{
		self.lexer.tokens.get(self.tok_pos).s.clone()
	}
	
	fn token_left(&self) -> uint
	{
		self.lexer.tokens.len()
	}
	
	fn next_token(&mut self)
	{
		//pop front token?
		self.lexer.tokens.pop_front();
	}
	
	fn next_tok_nws(&mut self)
	{
		while self.lexer.tokens.len() > 0
		&& self.cur_kind() == lexer::Whitespace  {
			self.next_token();
		}
	}
	
	
	pub fn parse(&mut self) -> Box<ast::AstNode>
	{
		//lex one line and generate tokens
		self.lexer.tokenize();
		
		//generate a List and 
		while self.lexer.tokens.len() > 0
		{
			self.parse_command();
		}
		
		return box ast::Empty;
	}
	
	fn parse_command(&mut self) -> Box<ast::AstNode>
	{
		//this is called when lexer has lexed one line?
		
		//keywords
		if self.cur_kind() == lexer::KwDef {
			return self.parse_def();
		}
		
		//keywords: let, if, etc
		
		//otherwise it is a command
		
		let mut cmd = box ast::CommandNode {exe: Vec::new(), args: Vec::new() };
		
		//first parse exe 
		loop 
		{
			match self.cur_kind()
			{
				lexer::Id => { cmd.exe.push(box ast::StringLiteral(self.cur_string()))}
				lexer::PlaceId => {cmd.exe.push(self.parse_expression()); }
				_ => {fail!();}
			}
			self.next_token();
			
			if self.cur_kind() == lexer::Whitespace {
				self.next_token();
				break;
			}
		}
		
		//parse arguments?
		
		while self.token_left() > 0
		{
			let mut arg = box ast::List(Vec::new());
			
			//parse a single argument until first whitespace
			loop 
			{
				match arg
				{
					box ast::List(ref mut arg_list) => 
					{
						match self.cur_kind()
						{
							lexer::Id => { arg_list.push(box ast::StringLiteral(self.cur_string()))}
							lexer::PlaceId => { arg_list.push(self.parse_expression()); }
							_ => {fail!();}
						}
					}
					_ => {fail!()}
				}
				self.next_token();
				
				if self.cur_kind() == lexer::Whitespace {
					self.next_token();
					break;
				}
			}
			cmd.args.push(arg);
		}
		
		return box ast::Command(cmd); //return command
	}
	
	fn parse_expression(&mut self) -> Box<ast::AstNode>
	{
		//precedence climbing
		fail!();
	}

	// def <name> : <type> {} or = <expr>
	fn parse_def(&mut self) -> Box<ast::AstNode>
	{
		//cur token = KwDef
		fail!();
	}

	//merge_token_until_whitespace?
}








#[test]
fn parser_test()
{
	//command
	//def func
	//def ...
	//let
	//expr
}
