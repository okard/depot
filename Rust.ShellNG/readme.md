# ShellNG

ShellNG implementation in rust


## Todo
* syntax mod with token, lexer, parser
* ContextTable renaming and handling (on stack?)
	- Node->Table Mapping???
* More Parsing stuff
	- definitions
	- expressions
* rename exec -> interpreter
* internal commands/functions
	- prompt
	- cd / pwd
	- exit
	- .
	- (and more)

* command line args and file handling
* think about wildcard abuse
* internal settings?
	- abort script on error (no go through all commands)
* think about commands with expression syntax
	- $foo.asd 
	- $foo + 1
	- abc$abc + 1
	- $foo+1
	- $abc -l$foo
* handle expression returns at command exe position possibilities:
	- ignore -> no command
	- string -> executable
	- array -> complete command with args? 
* think about let syntax


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
	
	def exec = "ls"
	$exec -l .
	
	def s = "s"
	l$s -l .	//do not allow $ident in compound command parts?
	
	
	date
	cat /usr/share/dict/words
	who >user.names
	who >>user.names
	wc <file
	echo [a-f]*.c
	who | wc
	who; date
	cc *.c &
	mkdir junk && cd junk
	cd ..
	rm -r junk || echo "rm failed!"
	
## Links
	https://github.com/michaelmacinnis/oh
	
