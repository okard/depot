
use std::rc::{Rc};

//objects

//process -> runtime object
//variable/value
//arrays/list
//maps

//pathes?

//definition?

//command nodes will be executed -> become process (removed from ast?)

#[deriving(Show)]
pub enum Node
{
	Nothing,
	
	////////////////////////////////////////////////////////////////////
	//Declarations/Statements:
	Command(Box<Command_>),
	
	
	////////////////////////////////////////////////////////////////////
	//Expressions:
	
	//UnaryExpr
	BinaryExpr(Box<BinaryExpr_>),
	//CallExpr 
	
	//Literals:
	StringLiteral(Box<String>),		//"asda" or abc
	VarLiteral(Box<String>),			//$abc
	
	//Special:
	List(Box<Vec<Node>>)	//concatenation of AstNodes result in a string -> abc$abc 
}

#[deriving(Show)]
pub struct Command_
{
	pub exe: Node, //executable
	pub args: Node //the parameters
}

#[deriving(Show)]
enum BinOp
{
	Access,
	Plus,
	Minus,
	Mul,
	Div,
}

#[deriving(Show)]
pub struct BinaryExpr_
{
	left: Node,
	op: BinOp,
	right: Node
}



//helper like merge list

