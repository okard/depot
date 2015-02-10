
use std::old_io;

/**
* Script Input
* can be a file or line(stdin)
*/
pub trait SourceInput
{
	//temp/non temp source?
	
	//the lex/parse input
	
	fn read_line(&mut self) -> old_io::IoResult<String>;
	fn prompt<'a>(&'a self) -> &'a str; //Option?
	fn prompt_update(&mut self, &str);
	
	fn has_prompt(&self) -> bool 
	{
		false
	}
	
	
	//line/offset/size -> for file handling
	
	
	//todo reduce to read() ???
	
	
	//only required for interactive user input? 
		//prompt
		//history?
		//completion callbacks?
}

/**
* Interface for stdin, stdout, stderr
* can be mapped on local stdin/stdout/stderr
* or on a socket or other
* can share stdin with SourceInput
*/
pub trait ShellIO
{
	//interface:
	
	//standard fds:
	//0 	Standard input 	STDIN_FILENO 	stdin
	//1 	Standard output 	STDOUT_FILENO 	stdout
	//2 	Standard error 	STDERR_FILENO 	stderr
	
	//other fds? (this trait can be bind to a process)

	//input and output streams
	//required as fd_int???
}


pub mod buffer;
pub mod linenoise;


