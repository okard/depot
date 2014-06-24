
use ant::{AntEntity};
use action::{Action};


//communicate to ai
pub trait Ai 
{
	
	//todo HiveInterface as reference????
	fn new_ant(&mut self) -> Box<AntEntity>;
	fn update_ant(&mut self, id: u32, &mut Box<AntEntity>) -> Action;
	
	//inform about errors?
		//ant want to work not dead yet beetle and so on 
}

//Interface that an ai can use
pub trait HiveInterface 
{
	
	//entities_in_range(id);
	
	//hive info
		//category stats
		
		//catogoryid <-> count
		
		
	// hill info
	
	//retrieve global messages
	//retrieve node messages
	
	//find next hill
	//find ants in range
}
