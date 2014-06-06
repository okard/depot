# ShellNG

ShellNG implementation in rust



## Lexing
* Whitespace aware 
	- whitespace token?
	- for $abc.abc.abc expressions?
* Escaping
	- ls -l test\ folder
	- ls -l "test folder"
	 


## Test Notices
	ls -l
	ls -l *.sh 	//wildcards
	
	def a = "*.sh"
	ls -l $a.get_files()
	
	