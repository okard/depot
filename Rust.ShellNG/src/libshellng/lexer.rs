
use std::io;
use std::io::stdio;
use collections::ringbuf::{RingBuf};
use collections::deque::{Deque};


pub enum Token
{
	Eof,		//end
	Id(String),		 // <id>
	PlaceId(String), // $<id>
	KwDef,			 // def
	
					// (, ), [, ], ... 
	
	OpPlus,			 // +
	OpAssign,		 // =
	OpDot			 // .
}

//todo reader interface which supports prompt???


pub struct Lexer<'a>
{
	reader: & 'a mut io::Buffer,
	pub tokens: RingBuf<Token>
	
}


impl<'a> Lexer<'a>
{
	pub fn new(reader: &mut io::Buffer) -> Lexer
	{
		Lexer { reader: reader, tokens: RingBuf::with_capacity(5)}
	}
	
	fn tokenize_part(&mut self, part: &str)
	{
		let deque = &mut self.tokens as &mut Deque<Token>;
		
		if part.char_at(0) == '$'
		{
			deque.push_back(PlaceId(part.to_str()));
			return; 
		}
		
		if part.len() == 1 
		&& part.char_at(0) == '.'
		{
			deque.push_back(OpDot);
			return; 
		}
		
		//if nothing else its a id
		deque.push_back(Id(part.to_str()));
	}
	
	//tokenize a complete line
	//line stands here for the buffer to tokenize
	fn tokenize_line(&mut self, line : &String)
	{
		let mut line_slice = line.as_slice();
		let mut startpos = 0;
		let mut curpos = 0;
		
		//determine a part between whitespaces
		//check parts belonging
		
		// let $foo = $foo+1 is invalid?
		
		loop 
		{
			//handle as byte
			//char at fails with unicode chars -.-
			if line_slice.char_at(curpos).is_whitespace()
			{
				let part = line_slice.slice_chars(startpos, curpos);
				
				//tokenize part
				self.tokenize_part(part);

				//find next starting token
				startpos = curpos;
				while line_slice.char_at(startpos).is_whitespace()
				{
					startpos = startpos + 1;
					curpos = curpos + 1;
					
					if curpos >= line_slice.len() 
					|| startpos >= line_slice.len() {
						break;
					}
				}
			}
			
			curpos = curpos + 1;
			
			if curpos >= line_slice.len() {
				break;
			}
		}
	}
	
	//this generates a bunch of tokens? 
	//return a result?
	pub fn tokenize(&mut self)
	{
		//read in
		let input = self.reader.read_line();
		
		match input
		{
			Ok(ref line) => 
			{
				self.tokenize_line(line)
			}
			Err(err) => 
			{ 
				println!("{}", err); 
				//enque token eof
			}
		}
		
		//when runs to the end of a line and it is escaped read again
	}
}
