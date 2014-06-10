

//objects

//process -> runtime object
//variable/value
//arrays/list
//maps

//pathes?

//definition?

//command nodes will be executed -> become process

pub enum AstNode
{
	Empty,
	Command(Box<CommandNode>),
	StringLiteral(String),		//"asda" or abc
	VarLiteral(String),			//$abc
	
	List(Vec<Box<AstNode>>)	//concatenation of AstNode -> abc$abc 
}

pub struct CommandNode
{
	pub exe: Vec<Box<AstNode>>, //exe also Vec for exe for ls$abc -l stuff
	pub args: Vec<Box<AstNode>> // one parameter is a List node
}


