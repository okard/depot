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
	
    detect wildcards
    
    special: 
        && 
        || 
        | 
        <
        >
        >>
        &
        
## Special internal objects
    $sys
        $sys.prompt     //shell prompt
        $sys.process    //shell process see $process object
        $sys.file       //current executed file if available
        $sys.cwd        //current working directory
        
        $sys.exit(int)  //exit shell process with id
        
    $process
        $process.pid    //process id
        $process.gid    //group id
        $process.uid    //user id
        
    $env    //enviroment variables
    
    $fs
    
    $date    
        
	
# EBNF

program := { definition | statement }
		 
         
definition := definition_obj
            | definition_func
            | definition_str
            | definition_num;

definition_obj := "def", identifier, ":", "object", [ "{", { obj_def }, "}"];
definition_func := "def", identifier, ":", "function", [ "{", { function_def }, "}"];
definition_str := "def", identifier, ":", "string", [ "=", expression];
definition_num := "def", identifier, ":", "number", [ "=", expression];
definition_arr := "def", identifier, ":", "array", [ "=", expression];
definition_map := "def", identifier, ":", "map", [ "=", expression];

statement := statement_if
           | statement_for
           | statement_while
           | statement_command
           | statement_expression;
         
         
statement_command := com_part , { com_part };

com_part := string
          | com_identifier;  
           
        
expression := expression_binary
            | expression_unary
            | expression_command
            | expression_id
            | expression_call
            | expression_index;
                     
expression_id := "$", identifier, {".", identifier};

expression_command := "$", "(", command, ")";
             
expression_binary := expression binary_operator expression;

expression_unary := expression unary_operator
                  | unary_operator expression;
                  
expression_call := expression, "(", {expression}, ")";

expression_index := expression, "[", {expression}, "]";


identifier := char, { char | digit };
com_identifier := all_char, { all_char };
string := """, ? all chars exclude " ?, """ 
number_int := digit, { digit };
number_float := number_int, ".f" | number_int, ".", digit, {digit};
digit = ? [0-9] ?;
char = ? [a-zA-Z_] ?;
all_char = ? all readable chars exclude control characters ? 


	
