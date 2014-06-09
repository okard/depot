
use std::io;
use std::path;
use std::vec;
use collections::ringbuf::{RingBuf};
use collections::deque::{Deque};

use helper;

pub enum TokenKind
{
	Eof,
	Id,
	PlaceId,
	StringLiteral,
	NumLiteral,
	
	KwDef,			 // def
					 // let
					 // if, for, match, ...
	
					// (, ), [, ], ... 
	SymROBracket,	// (
	SymRCBracket,	// )
	
	SymDollar,		// $
	
	OpPlus,			 // +
	OpAssign,		 // =
	OpDot,			 // .
	
	Whitespace,
}

pub struct Token
{
	kind: TokenKind,
	s : String
}

#[deriving(PartialEq)]
impl Token
{
	pub fn new(kind: TokenKind, s : &str) -> Token
	{
		Token { kind:kind, s: String::from_str(s) }
	}
}

impl PartialEq for Token 
{
     fn eq(&self, other: &Token) -> bool 
     {
         (self.kind as int == other.kind as int)
         && (self.s == other.s)
     }
 }




//todo reader interface which supports prompt???
	// ShellSource trait


pub struct Lexer<'a>
{
	reader: & 'a mut io::Buffer,
	pub tokens: RingBuf<Token>
	
	//position?
	//Unicode reader here?
	//mode for switching between command mode / expression mode
}


impl<'a> Lexer<'a>
{
	pub fn new(reader: &mut io::Buffer) -> Lexer
	{
		Lexer { reader: reader, tokens: RingBuf::with_capacity(5)}
	}
	
	fn whitespace_tok_check(&mut self, reader: &mut helper::CharReader)
	{
		//whitespace check
		if !reader.is_eob() 
		&& reader.cur_char().is_whitespace() {
			self.tokens.push_back(Token::new(Whitespace, " "));
		}
	}
	
	//creates a single token
	fn tokenize_part(&mut self, reader: &mut helper::CharReader) -> bool
	{
		//nothing to do
		if reader.is_eob() {
			return false;
		}
		
		//skip preleading whitespace
		while !reader.is_eob()
		&& reader.cur_char().is_whitespace()
		{
			reader.next_char();
		}
		
		//read over buffer no token here (whitespaces at end)
		if reader.is_eob() {
			return false;
		}
		
		//safe position of first valid char
		let start_pos = reader.pos();
		let mut tok_kind : TokenKind = Eof;
		
		//if it is an id parse it to end
		if reader.cur_char().is_alphanumeric()
		{
			tok_kind = Id;
			
			//read over until something other occur
			while !reader.is_eob()
			&& reader.cur_char().is_alphanumeric() {
				reader.next_char();
			}
			
			self.tokens.push_back(Token::new(tok_kind, reader.part().slice(start_pos, reader.pos())));
			self.whitespace_tok_check(reader);
			
			return true;
		}
		
		//read numbers
		
		
		//handling of other stuff
		match reader.cur_char() 
		{
			'$' => 
			{ tok_kind = SymDollar; 
			  reader.next_char();
				//followed by alphanumeric = PlaceId Parse complete?
			}
			
			'\\' => { /* handle escape! */ }
			
			'"' => { /* todo read string */ }
			_ => ()
		}
		
		reader.next_char();
		
		//if at the end of reading a whitespace is the "next" char 
		//	add a whitespace token
		self.whitespace_tok_check(reader);
		
		return true;
	}
	
	//TokenKind
	
	//this generates a bunch of tokens? 
	//return a result?
	pub fn tokenize(&mut self) -> bool
	{
		//read in
		let input = self.reader.read_line();
		
		//handle as u8 slice
		//read chars to 32 bit utf32 char
		//as_bytes
		
		match input
		{
			Ok(ref line) => 
			{
				//tokenize complete line?
				let mut reader = helper::CharReader::new(line.as_slice());
				while self.tokenize_part(&mut reader) {
				}
				return true;
			}
			Err(err) => 
			{ 
				println!("{}", err); 
				//enque token eof
				return false;
			}
		}
		
		//when runs to the end of a line and it is escaped read again
	}
}


#[test]
fn lexer_test()
{
	let test_string = String::from_str("foo 14 bar $abc $abc+1 $abc + 1");
	let mut reader = io::MemReader::new(test_string.into_bytes());
	let mut lexer = Lexer::new(&mut reader as &mut Buffer);
	
	let mut list = vec::Vec::new();
	list.push(Token::new(Id, "foo"));
	list.push(Token::new(Whitespace, " "));
	//list.push(Token::new(NumLiteral, "14"));
	
	assert!(lexer.tokenize()); //tokenize should return true
	
	for i in range(0, list.len()) 
	{
		assert!(lexer.tokens.get(i) ==  list.get(i));
	}
	
	
	//multiline, escaping tests, ...
}
