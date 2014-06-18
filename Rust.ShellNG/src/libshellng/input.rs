use std::io;

//input trait
pub trait ShellInput
{
	fn read_line(&mut self) -> io::IoResult<String>;
	fn prompt<'a>(&'a self) -> &'a str; //Option?
	fn prompt_update(&mut self, &str);
	
	fn has_prompt(&self) -> bool 
	{
		false
	}
	
	//shellio  ?
		//input and output streams
	
	//history 
	
	//completion callbacks?
}


pub struct ShellBufferInput<'a> 
{
	buf: & 'a mut io::Buffer,
	prompt: Option<String>
}

impl<'a> ShellBufferInput<'a>
{
	pub fn new(buf: &mut io::Buffer) -> ShellBufferInput
	{
		ShellBufferInput { buf: buf, prompt: None }
	}
}

impl<'a> ShellInput for ShellBufferInput<'a>
{
	fn read_line(&mut self) -> io::IoResult<String>
	{
		if !self.has_prompt()
		{
			print!("{}", self.prompt);
		}
		self.buf.read_line()
	}
	
	fn prompt<'a>(&'a self) -> &'a str
	{
		if self.prompt.is_some() {
			self.prompt.get_ref().as_slice()
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
	
	fn has_prompt(&self) -> bool 
	{
		true
	}
}


