
use std::io;

//input trait
pub trait ShellInput
{
	fn read_line(&mut self) -> io::IoResult<String>;
	fn prompt<'a>(&'a self) -> &'a str;
	fn prompt_update(&mut self, &str);
	
	
	//history 
	
	//completion callbacks?
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
		print!("{}", self.prompt);
		self.buf.read_line()
	}
	
	fn prompt<'a>(&'a self) -> &'a str
	{
		self.prompt.as_slice()
	}
	
	fn prompt_update(&mut self, prompt: &str)
	{
		//simple replace?
		self.prompt = String::from_str(prompt);
	}
}

pub struct ShellNoiseInput
{
	pub prompt: String
}


impl ShellInput for ShellNoiseInput
{
	fn read_line(&mut self) -> io::IoResult<String>
	{
		let line = ::rustnoise::rustnoise(self.prompt.as_slice());
		
		if line.is_null() {
			return Err(io::IoError { kind: io::InvalidInput, 
								desc: "No input given", 
								detail: None });
		}
		
		Ok(String::from_str(line.as_str().unwrap()))
	}
	
	fn prompt<'a>(&'a self) -> &'a str
	{
		self.prompt.as_slice()
	}
	
	fn prompt_update(&mut self, prompt: &str)
	{
		//simple replace?
		self.prompt = String::from_str(prompt);
	}
}


//linenoise





