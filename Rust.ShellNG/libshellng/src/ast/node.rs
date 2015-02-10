
//objects

//process -> runtime object
//variable/value
//arrays/list
//maps

//pathes?

//definition?

//command nodes will be executed -> become process (removed from ast?)

#[derive(Debug)]
pub enum Node
{
	Nothing,
	
	////////////////////////////////////////////////////////////////////
	//Declarations/Statements:
	Command,
	
	
	////////////////////////////////////////////////////////////////////
	//Expressions:
	
	UnaryExpr(Box<UnaryExpr_>),
	BinaryExpr(Box<BinaryExpr_>),
	//CallExpr 
	
	//Literals:
	StringLiteral(Box<String>),		//"asda" or abc
	VarLiteral(Box<String>),			//$abc
	
	
	//process result? -> ls || ls; ls && ls;
		//-> NumLiteral
	
	//Special:
		//different type of list nodes? 
		//rename to mergelist
		// a Program(List) type?
	List(Box<Vec<Node>>)	//concatenation of AstNodes result in a string -> abc$abc 
}


/*
Command {
		exe: Node, //executable
		args: Vec<Node> //the parameters
		
		//pipes fds and so on
	},
*/

#[derive(Debug)]
pub enum UnOp
{
	Not,
	PreMinus,
	PrePlus
}

#[derive(Debug)]
pub struct UnaryExpr_
{
	pub expr: Node,
	pub op : UnOp
}

#[derive(Debug)]
enum BinOp
{
	Access,	// .
	Plus,	// +
	Minus,	// -
	Mul,	// *
	Div,	// /
}

#[derive(Debug)]
pub struct BinaryExpr_
{
	left: Node,
	op: BinOp,
	right: Node
}


//helper like merge list

