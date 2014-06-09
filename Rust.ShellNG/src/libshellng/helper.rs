
use std::str;






pub struct CharReader<'a>
{
	part: & 'a str,
	pos: uint
}

impl<'a> CharReader<'a>
{
	pub fn new<'a>(part: &'a str) -> CharReader<'a>
	{
		CharReader { part:part, pos:0 }
	}
	
	pub fn is_eob(&self) -> bool
	{
		self.pos >= self.part.len()
	}
	
	pub fn cur_char(&self) -> char
	{
		assert!(!self.is_eob());
		self.part.char_at(self.pos)
	}
	
	pub fn next_char(&mut self) 
	{
		let c = self.cur_char();
		self.pos += c.len_utf8_bytes();
	}
	
	pub fn part(&mut self) -> &'a str
	{
		self.part
	}
	
	pub fn pos(&self) -> uint
	{
		self.pos
	}
}

#[test]
fn charreader_test()
{
	let test_string = "abc äüö -.,";
	let mut reader = CharReader::new(test_string);
	
	assert!(reader.pos() == 0);
	
	assert!(reader.cur_char() == 'a');
	reader.next_char();
	assert!(reader.pos() == 1);
	
	assert!(reader.cur_char() == 'b');
	reader.next_char();
	assert!(reader.pos() == 2);
	
	
}




