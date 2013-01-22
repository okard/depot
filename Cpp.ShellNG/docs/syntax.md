# ShellNG Syntax


## Keywords

Keywords introduce a special context for parsing

	def
	if, for, while, 


## Variables and Objects

	def name: type 
	
type	
	* object - creates a basic object (requires definition)
	* function - creates a function (requires definition)
	* string - creates a string
	* number - creates a number
	* #<objectname> - create a clone of another object
	* array(type) 
	* map(type, type)
	

## Expressions

	$name = $foo()
	$name = 1+4
	$name = $name + 6
	$name.name.name()
	
	
	$id = $exec(["ls", "-alh", "."])  (exec(array(string))
	$id = $exec("ls", "-alh", ".") 
	$id = $exec("ls -alh .")		  (exec(string))
	
## Commands

	echo test
	echo $foo
	echo "$foo"
	
	
	
# EBNF

program := definition
		 | statement
		 | expression
		 | command
		 
	
definition := "def", identifier, ":", def_type;


definition_obj := "def", identifier, ":", "object", [ "{", { obj_def }, "}"];

definition_function := 

def_type := "object"
		  | "function"
		  | "string"
		  | "number"
		  | "#" identifier;
		  
statement := statement_if
           | statement_for
           | statement_while;
           
expression := expression_assign
            | expression_binary
            
            
expression_access := "$", identifier, {".", identifier};
             
		  
command := identifier, { identifier };

argument := """, {all_char} ,"""
		  | identifier
		  | number
		  | "$", identifier;

		  
identifier := char, { char | digit };
number_int := digit, { digit };
number_float := number_int, ".f" | number_int, ".", digit, {digit};
digit = ? [0-9] ?;
char = ? [a-zA-Z_-] ?;


	
