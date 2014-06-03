
use std::io;
use std::io::stdio;


enum Token
{
	Eof,		//end
	Id(String),
	KwDef,
	
	OpPlus,
	OpAssign
}


pub struct Lexer<'a>
{
	reader: & 'a mut io::Buffer
	
	//token list to fill?
	//collections::ringbuf::RingBuf
}


impl<'a> Lexer<'a>
{
	pub fn new(reader: &mut io::Buffer) -> Lexer
	{
		Lexer { reader: reader}
	}
	
	
	fn tokenize_line(&mut self, line : &String)
	{
		let mut line_slice = line.as_slice();
		let mut startpos = 0;
		let mut curpos = 0;
		
		loop 
		{
			if line_slice.char_at(curpos).is_whitespace()
			{
				let part = line_slice.slice_chars(startpos, curpos);
				
				stdio::println(part.trim());
				//println!("{}", part);
				startpos = curpos;
			}
			
			curpos = curpos + 1;
			
			if curpos >= line_slice.len() {
				break;
			}
		}
	}
	
	//this generates a bunch of tokens?
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
			Err(err) => { println!("{}", err); }
		}
		
		//when runs to the end of a file and it is escaped read again
	}
}
