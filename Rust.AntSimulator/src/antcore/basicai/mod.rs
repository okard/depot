
use interface::{HiveInterface, Ai};
use ant::{AntEntity};
use action::{Action};


pub struct BaseAI<'a>
{
	hive: &'a HiveInterface
}

impl<'a> BaseAI<'a> 
{
	pub fn new<'a>(hive: &'a HiveInterface) -> BaseAI<'a>
	{
		BaseAI { hive: hive }
	}
}




impl<'a> Ai for BaseAI<'a>
{
	fn new_ant(&mut self) -> Box<AntEntity>
	{
		box AntEntity::new()
	}
	
	fn update_ant(&mut self, id: u32, ant: &mut Box<AntEntity>) -> Action
	{
		::action::None
	}
}
