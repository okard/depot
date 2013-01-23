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

program := { definition | statement }
		 

definition_obj := "def", identifier, ":", "object", [ "{", { obj_def }, "}"];
definition_obj := "def", identifier, ":", "function", [ "{", { function_def }, "}"];
definition_obj := "def", identifier, ":", "string", [ "=", expression];
definition_obj := "def", identifier, ":", "number", [ "=", expression];

		  
statement := statement_if
           | statement_for
           | statement_while;
           | statement_command
           
expression := expression_assign
            | expression_binary
            | expression_command
            
            
expression_access := "$", identifier, {".", identifier};


expression_command := "$", "(", command, ")";
             
		  
statement_command := identifier, { identifier };

argument := """, {all_char} ,"""
		  | identifier
		  | number
		  | "$", identifier;



		  
identifier := char, { char | digit };
com_identifier := all_char, { all_char };
number_int := digit, { digit };
number_float := number_int, ".f" | number_int, ".", digit, {digit};
digit = ? [0-9] ?;
char = ? [a-zA-Z_] ?;
all_char = ? all readable chars exclude control characters ? 


	
