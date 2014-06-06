
use std::io;
use collections::ringbuf::{RingBuf};
use collections::deque::{Deque};

use helper::{uchar, UnicodeReader};

pub enum TokenKind
{
	Eof,
	Id,
	PlaceId,
	StringLiteral,
	
	KwDef,			 // def
					 // let
					 // if, for, match, ...
	
					// (, ), [, ], ... 
	SymROBracket,	// (
	SymRCBracket,	// )
	
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

impl Token
{
	pub fn new(kind: TokenKind, s : &str) -> Token
	{
		Token { kind:kind, s: String::from_str(s) }
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
	
	//creates a single token
	fn tokenize_part(&mut self, reader: &mut UnicodeReader) -> bool
	{
		let mut cur_res = reader.read_char();
		
		//skip preleading whitespace
		while !cur_res.is_eob()
		&& UnicodeReader::is_whitespace(cur_res.get_char()) 
		{
			cur_res = reader.read_char();
		}
		
		//read over buffer no token here
		if reader.is_eob()
		|| cur_res.is_eob() {
			return false;
		}
		
		//have valid first char here?
		
		//safe start position (to extract ident, string, ... via utf8 slice
		let start_pos = reader.pos();
		
		//create slice from here to next whitespace?
			//pay attention when \ followed by whitespace occur
			//whitespace gets escaped 
		
		
		//if we have readed complete stuff add token
			//detect token kind afterwards
			//detect wildcards? (regex)
		
		//add whitespace token afterwards?
			
		//ascii char
		if cur_res.get_char() < 0x7F 
		{
			let ascii_char : char = (cur_res.get_char() as u8) as char;
			
			match ascii_char 
			{
				'$' => { }
				_ => ()
			}
			
			//follow up
		}
		return true;
	}
	
	//tokenize a complete line
	//line stands here for the buffer to tokenize
	fn tokenize_line(&mut self, line : &[u8])
	{
		//as_bytes &'a [u8]
		let mut reader = UnicodeReader::new(line); 
		
		//doit until end of line
		while self.tokenize_part(&mut reader){		
		}
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
				self.tokenize_line(line.as_bytes());
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
