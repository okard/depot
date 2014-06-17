# ShellNG

ShellNG implementation in rust


## Todo
* linenoise/readline for line handling?

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
	l$s -l .
	
	
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
	
