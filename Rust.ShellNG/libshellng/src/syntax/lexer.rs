
//use std::vec;
use std::collections::{RingBuf};

use io;
use helper;

#[derive(Copy)]
pub enum TokenKind
{
	Eof,			
	Id,				//foo
	PlaceId,		//$bar
	StringLiteral,	//"lit"
	NumLiteral,
	
	KwDef,			// def
	KwLet,			// let
	KwIf,			// if
	KwFor,			// for
	KwMatch,		// match
	
	SymROBracket,	// (
	SymRCBracket,	// )
	SymSOBracket,	// [
	SymSCBracket,	// ]
	SymCOBracket,	// {
	SymCCBracket,	// }
	
	OpDot,			// .
	OpAssign,		// =
	OpPlus,			// +
	OpMinus,		// -
	OpMul,			// *
	OpDiv,			// /
	
	//special shell chars
	Pipe,			// | pipe symbol
	Comma,			// ,
	Ambersand,		// &
	
	And,			// &&
	Or,				// ||
	
	//Redirecting:
		// > < redirect stdout
		// 2> 
		// 2>&1
		// >&2
		// >>
		//num>string
		//num>&num
		//num>>string
		//num>>&num
		// <> 
	
	Comment,	
	
	Whitespace,
	//NewLine?
}

impl PartialEq for TokenKind 
{
     fn eq(&self, other: &TokenKind) -> bool 
     {
         self == other
     }
}

pub struct Token
{
	pub kind: TokenKind,
	pub s : String
}

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
         self.kind == other.kind
         && self.s == other.s
     }
 }


//todo reader interface which supports prompt???
	// ShellStdinReader  impl ReaderTrait?
	// special trait with .print_prompt support?

pub struct Lexer<'a>
{
	reader: & 'a mut (io::SourceInput + 'a), //buffer is minimal interface here can also be reader
	pub tokens: RingBuf<Token>
	
	//position?
	//Unicode reader here?
	//mode for switching between command mode / expression mode
}


impl<'a> Lexer<'a>
{
	pub fn new<'b>(input: & 'b mut io::SourceInput) -> Lexer<'b>
	{
		Lexer { reader: input, tokens: RingBuf::with_capacity(5)}
	}
	
	fn whitespace_tok_check(&mut self, reader: &mut helper::CharReader)
	{
		//whitespace check
		if !reader.is_eob() 
		&& reader.cur_char().is_whitespace() {
			self.tokens.push_back(Token::new(TokenKind::Whitespace, " "));
		}
	}
	
	fn check_id_token(t : &mut Token)
	{
		if t.kind != TokenKind::Id {
			return;
		}
		
		match t.s.as_slice()
		{
			"def" => {t.kind = TokenKind::KwDef; }
			"let" => {t.kind = TokenKind::KwLet; }
			"if" => {t.kind = TokenKind::KwIf; }
			"for" => {t.kind = TokenKind::KwFor; }
			"match" => {t.kind = TokenKind::KwMatch; }
			_ => ()
		}
		//compare with keywords
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
		&& reader.cur_char().is_whitespace() {
			reader.next_char();
		}
		
		//read over buffer no token here (whitespaces at end)
		if reader.is_eob() {
			return false;
		}
		
		//safe position of first valid char
		let mut start_pos = reader.pos();
		let mut tok_kind = TokenKind::Eof;
		
		//read numbers
		if reader.cur_char().is_digit(10)
		{
			tok_kind = TokenKind::NumLiteral;
			
			//escaping
			
			//read over until something other occur
			while !reader.is_eob()
			&& reader.cur_char().is_digit(10) {
				reader.next_char();
			}
			
			self.tokens.push_back(Token::new(tok_kind, reader.part().slice(start_pos, reader.pos())));
			self.whitespace_tok_check(reader);
			return true;
		}
		
		//if it is an id parse it to end
		if reader.cur_char().is_alphanumeric()
		{
			tok_kind = TokenKind::Id;
			
			//escaping
			
			//read over until something other occur
			while !reader.is_eob()
			&& reader.cur_char().is_alphanumeric() {
				reader.next_char();
			}
			
			let mut tok = Token::new(tok_kind, reader.part().slice(start_pos, reader.pos()));
			Lexer::check_id_token(&mut tok);
			self.tokens.push_back(tok);
			self.whitespace_tok_check(reader);
			return true;
		}
		
		
		//handling single symbols
		match reader.cur_char() 
		{
			'(' => { tok_kind = TokenKind::SymROBracket; reader.next_char(); }
			')' => { tok_kind = TokenKind::SymRCBracket; reader.next_char(); }
			'[' => { tok_kind = TokenKind::SymSOBracket; reader.next_char(); }
			']' => { tok_kind = TokenKind::SymSCBracket; reader.next_char(); }
			'{' => { tok_kind = TokenKind::SymCOBracket; reader.next_char(); }
			'}' => { tok_kind = TokenKind::SymCCBracket; reader.next_char(); }
			
			'=' => { tok_kind = TokenKind::OpAssign; reader.next_char(); }
			'.' => { tok_kind = TokenKind::OpDot; reader.next_char(); }
			
			'+' => { tok_kind = TokenKind::OpPlus; reader.next_char(); }
			'-' => { tok_kind = TokenKind::OpMinus; reader.next_char(); }
			'*' => { tok_kind = TokenKind::OpMul; reader.next_char(); }
			'/' => { tok_kind = TokenKind::OpDiv; reader.next_char(); }
			
			'|' => { tok_kind = TokenKind::Pipe; reader.next_char(); }
			
			'$' => { tok_kind = TokenKind::PlaceId; reader.next_char(); }
			
			'\\' => { panic!(); /* handle escape! */  }
			
			'"' => { tok_kind = TokenKind::StringLiteral;  }
			
			'#' => { return false; } //ignore complete line
			
			_ => { reader.next_char(); }
		}
		
		// 2 chars or special stuff 
		match tok_kind
		{
			TokenKind::PlaceId => 
			{
				//while not whitespace read
				while !reader.is_eob()
				&& reader.cur_char().is_alphanumeric() {
					reader.next_char();
				}
			}
			
			TokenKind::StringLiteral =>
			{
				assert!(reader.cur_char() == '"');
				reader.next_char();
				start_pos = reader.pos();
				
				while !reader.is_eob()
				&& reader.cur_char() != '"' {
					reader.next_char();
				}
				assert!(reader.cur_char() == '"');
			}
			
			_ => ()
		}

		//creates the token
		self.tokens.push_back(Token::new(tok_kind, reader.part().slice(start_pos, reader.pos())));
		
		//skip end "
		if tok_kind == TokenKind::StringLiteral {
			assert!(reader.cur_char() == '"');
			reader.next_char();
		}
		

		//if at the end of reading a whitespace is the "next" char 
		//	add a whitespace token
		self.whitespace_tok_check(reader);
		
		return true;
	}
	
	//TokenKind
	
	//todo rename to tokenize_line() ?
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
				while self.tokenize_part(&mut reader) {}
				//at end of buffer?
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
	use std::io;
	use std::vec;
	//todo split into multiple small tests
	//fix test string to contains all tokens incl. whitespace stuff
	
	let test_string = String::from_str("foo 14 bar $abc $abc+1 $abc + 1 ()[]{}.=+-*/\"string\"abc");
	let mut reader = io::MemReader::new(test_string.into_bytes());
	let mut lexer = Lexer::new(&mut reader as &mut Buffer);
	
	let mut list = vec::Vec::new();
	list.push(Token::new(Id, "foo"));
	list.push(Token::new(Whitespace, " "));
	list.push(Token::new(NumLiteral, "14"));
	list.push(Token::new(Whitespace, " "));
	list.push(Token::new(Id, "bar"));
	list.push(Token::new(Whitespace, " "));
	list.push(Token::new(PlaceId, "$abc"));
	list.push(Token::new(Whitespace, " "));
	list.push(Token::new(PlaceId, "$abc"));
	list.push(Token::new(OpPlus, "+"));
	list.push(Token::new(NumLiteral, "1"));
	list.push(Token::new(Whitespace, " "));
	list.push(Token::new(PlaceId, "$abc"));
	list.push(Token::new(Whitespace, " "));
	list.push(Token::new(OpPlus, "+"));
	list.push(Token::new(Whitespace, " "));
	list.push(Token::new(NumLiteral, "1"));
	list.push(Token::new(Whitespace, " "));
	//symbols 
	list.push(Token::new(SymROBracket, "("));
	list.push(Token::new(SymRCBracket, ")"));
	list.push(Token::new(SymSOBracket, "["));
	list.push(Token::new(SymSCBracket, "]"));
	list.push(Token::new(SymCOBracket, "{"));
	list.push(Token::new(SymCCBracket, "}"));
	//operator .=+-*/
	list.push(Token::new(OpDot, "."));
	list.push(Token::new(OpAssign, "="));
	list.push(Token::new(OpPlus, "+"));
	list.push(Token::new(OpMinus, "-"));
	list.push(Token::new(OpMul, "*"));
	list.push(Token::new(OpDiv, "/"));
	list.push(Token::new(StringLiteral, "string"));
	list.push(Token::new(Id, "abc"));
	
	assert!(lexer.tokenize()); //tokenize should return true
	
	for i in range(0, list.len()) 
	{
		println!("{} => '{}' == '{}' && {} == {}",i, 
				 lexer.tokens.get(i).s, list.get(i).s,
				 lexer.tokens.get(i).kind as isize, list.get(i).kind as isize);
		assert!(lexer.tokens.get(i) ==  list.get(i));
	}
	
	//multiline, escaping tests, ...
}
