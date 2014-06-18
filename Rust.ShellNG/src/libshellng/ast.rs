
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

#[deriving(Show)]
pub struct Command_
{
	pub exe: Node, //executable
	pub args: Vec<Node> //the parameters
	//redirections
	//piping
}

#[deriving(Show)]
pub enum UnOp
{
	Not,
	PreMinus,
	PrePlus
}

#[deriving(Show)]
pub struct UnaryExpr_
{
	pub expr: Node,
	pub op : UnOp
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

