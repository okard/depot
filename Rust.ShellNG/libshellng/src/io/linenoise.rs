use io::{SourceInput};

use std::old_io;
use std::old_path::BytesContainer;

pub struct ShellNoiseInput
{
	pub prompt: String
}

impl ShellNoiseInput
{
	pub fn new(prompt : &str) -> ShellNoiseInput
	{
		ShellNoiseInput {
				prompt: prompt.to_string()
		}
	}
}

impl SourceInput for ShellNoiseInput
{
	fn read_line(&mut self) -> old_io::IoResult<String>
	{
		let line = ::rustnoise::rustnoise(self.prompt.as_slice());
		
		if line.as_bytes().len() == 0 {
			return Err(old_io::IoError { kind: old_io::InvalidInput, 
								desc: "No input given", 
								detail: None });
		}
		
		/*
			pub fn linenoiseHistoryAdd(line: *::libc::c_char) -> ::libc::c_int;
			pub fn linenoiseHistorySetMaxLen(len: ::libc::c_int) -> ::libc::c_int;
		*/
		
		//add to history
		::rustnoise::rustnoise_history_add(line.container_as_str().unwrap());
		
		Ok(String::from_str(line.container_as_str().unwrap()))
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
