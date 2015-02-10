use std::old_io;
use io::{SourceInput};

pub struct ShellBufferInput<'a> 
{
	buf: & 'a mut (old_io::Buffer +'a),
	prompt: Option<String>
}

impl<'a> ShellBufferInput<'a>
{
	pub fn new<'b>(buf: & 'b mut old_io::Buffer) -> ShellBufferInput<'b>
	{
		ShellBufferInput { buf: buf, prompt: None }
	}
}

impl<'a> SourceInput for ShellBufferInput<'a>
{
	fn read_line(&mut self) -> old_io::IoResult<String>
	{
		if !self.has_prompt()
		{
			//print!("{}", self.prompt.unwrap());
		}
		self.buf.read_line()
	}
	
	fn prompt(&self) -> &str
	{
		if self.prompt.is_some() {
			self.prompt.as_ref().unwrap().as_slice()
		}
		else {
			""
		}
	}
	
	fn prompt_update(&mut self, prompt: &str)
	{
		//simple replace?
		self.prompt = Some(String::from_str(prompt));
	}
	
	fn has_prompt(&self) -> bool 
	{
		self.prompt.is_some()
	}
}
