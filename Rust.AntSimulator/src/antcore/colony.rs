
use interface::{Ai};
use hill::{Hill};


pub struct Colony<'a> 
{
	pub colonyId : u32,
	pub ai_handler: &'a mut Ai,
	pub hills: Vec<Hill>,
}

