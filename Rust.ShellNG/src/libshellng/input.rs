
use std::io;

//input trait
trait ShellInput
{
	fn read_line(&mut self) -> io::IoResult<String>;
	fn prompt(&self) -> &str;
	fn prompt_update(&mut self, &str);
}


pub struct ShellBufferInput<'a> 
{
	buf: & 'a mut io::Buffer,
	prompt: String
}

impl<'a> ShellBufferInput<'a>
{
	pub fn new(buf: &mut io::Buffer) -> ShellBufferInput
	{
		ShellBufferInput { buf: buf, prompt: "> ".to_string()}
	}
}


impl<'a> ShellInput for ShellBufferInput<'a>
{
	fn read_line(&mut self) -> io::IoResult<String>
	{
		self.buf.read_line()
	}
	
	fn prompt<'b>(&self) -> &'b str
	{
		"TODO"
	}
	
	fn prompt_update(&mut self, prompt: &str)
	{
		//simple replace?
		self.prompt = String::from_str(prompt);
	}
}

//stdin
//file  (buffered reader)



//linenoise





