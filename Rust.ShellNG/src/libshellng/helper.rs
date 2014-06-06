

// error: invalid start utf8 symbol
//		  invalid or missing follow byte
//		  end of buffer

pub type uchar = u32;

enum UnicodeResult
{
	Ok(uchar),
	EOB,
	Error
}

impl UnicodeResult
{
	pub fn get_char(&self) -> uchar
	{
		match *self
		{
			Ok(c) => {  return c; }
			EOB => { fail!("EOB"); }
			Error => { fail!("Error") }
		}
	}
	
	pub fn is_error(&self) -> bool
	{
		match *self
		{
			Error => true,
			_ => false
		}
	}
	
	pub fn is_eob(&self) -> bool
	{
		match *self
		{
			EOB => true,
			_ => false
		}
	}
}


pub struct UnicodeReader<'a>
{
	buffer: & 'a [u8],
	pos: uint
}

impl<'a> UnicodeReader<'a>
{
	pub fn new<'a>(buffer: & 'a [u8]) -> UnicodeReader<'a>
	{
		UnicodeReader { pos: 0, buffer:buffer }
	}
	
	pub fn slice(&self)
	{
		//return a unicode utf8 slice from buffer
	}
	
	//all unicode chars fit in u32? 
	// return Result? endof buffer?
	pub fn read_char(&mut self) -> UnicodeResult
	{ 
		let mut c : uchar = 0; //to null
		
		if(self.pos >= self.buffer.len()) {
			return EOB;
		}
		
		let byte = self.buffer[self.pos];
		
		match byte
		{
			// 1 char start: 0xxxxxxx
			0x00..0x7F => { 
				c = (byte & 0x7F) as uchar; 
				self.pos = self.pos+1; //skip 2 char
			}
			
			// 2 char start: 110xxxxx 
			0xC0..0xDF => {
				assert!(self.buffer.len()-self.pos > 1);
				//check that the following byte has format 0x10xxxxxx
				assert!((self.buffer[self.pos+1] >> 6 ) == 2);
				
				let first = ((self.buffer[self.pos] & 0x1F) as uchar) << 6;
				let second = (self.buffer[self.pos+1] & 0x3F) as uchar;
				c =  first | second;
				self.pos = self.pos+2; //skip 2 char
			}
			
			// 3 char start: 1110xxxx
			0xE0..0xEF => {
				assert!(self.buffer.len()-self.pos > 2);
				//check that the following byte has format 0x10xxxxxx
				assert!((self.buffer[self.pos+1] >> 6 ) == 2);
				assert!((self.buffer[self.pos+2] >> 6 ) == 2);
				
				let first = ((self.buffer[self.pos] & 0x0F) as uchar) << 12;
				let second = ((self.buffer[self.pos+1] & 0x3F) as uchar) << 6;
				let third = ((self.buffer[self.pos+2] & 0x3F) as uchar) << 0;
				c = first | second | third;
				self.pos = self.pos+3; //skip 3 char
			}
			
			// 4 char start: 1111 0xxx
			0xF0..0xF7 => {
				assert!(self.buffer.len()-self.pos > 3);
				//check that the following byte has format 0x10xxxxxx
				assert!((self.buffer[self.pos+1] >> 6 ) == 2);
				assert!((self.buffer[self.pos+2] >> 6 ) == 2);
				assert!((self.buffer[self.pos+3] >> 6 ) == 2);
				
				let first = ((self.buffer[self.pos] & 0x07) as uchar) << 18;
				let second = ((self.buffer[self.pos+1] & 0x3F) as uchar) << 12;
				let third = ((self.buffer[self.pos+2] & 0x3F) as uchar) << 6;
				let fourth = ((self.buffer[self.pos+3] & 0x3F) as uchar) << 0;
				
				c = first | second | third | fourth;
				self.pos = self.pos+4; //skip 3 char
			}
			
			//5 and 6 char not in standard anymore?
			_ => { return Error; }
		}
		
		return Ok(c);
	}
	
	pub fn pos(&self) -> uint
	{
		self.pos
	}
	
	pub fn is_eob(&self) -> bool
	{
		return (self.buffer.len()-self.pos) < 0;
	}
	
	pub fn is_whitespace(c : uchar) -> bool
	{
		c == '\n' as uchar
		|| c == '\r' as uchar
	    || c == '\t' as uchar
	    || c == ' ' as uchar
	}
	
	//alpha
	//numeric
	//alphanumeric
	
	//symbol
	
}
