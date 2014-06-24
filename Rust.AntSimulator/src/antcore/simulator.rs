
use map::{Map};
use entity::{Entity};
use colony::{Colony};
use interface::{Ai, HiveInterface};


pub struct Simulator<'a> {
	running: bool,
	map: Map,
	entities: Vec<Entity>,
	
	// Ais 
	
	// Colony, Ai 
	
	colonies: Vec<Colony<'a>>,
}


impl<'a> Simulator<'a> {
	pub fn new<'a>() -> Simulator<'a>
	{
		Simulator {
			running: true,
			map: Map::new(),
			entities: Vec::new(),
			colonies: Vec::new(),
		}
	}
	
	pub fn add_colony(&mut self, ai_handler: &'a mut Ai) 
	{
		let id = self.colonies.len() as u32;
		self.colonies.push(Colony {
			colonyId: id,
			ai_handler: ai_handler,
			hills: Vec::new(),
		});
	}
	
	fn update(&mut self, timeElapsedMs: f32) -> bool 
	{
		//handle map update
			//spawn new entities
			
			//loop through colony->hills
			//update hill (spawn new ants)
			
		//colony update
		
		//update entities
			//ant: get colonyid, get_ai(colony_id).update() 
			//skip static entities
	
	
		self.running
	}
	
	
	//handle action
}

impl<'a> HiveInterface for Simulator<'a>
{
	
}


