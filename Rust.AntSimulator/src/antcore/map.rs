
use std::rand::random;
use std::rand::{Rng, SeedableRng, IsaacRng};


pub struct Map {
	seed: u32,
	width: u32,
	height: u32,
	
	//spawn rates
}


impl Map 
{
	pub fn new() -> Map 
	{
		let seed : u32 = random();
		let mut rng : IsaacRng = SeedableRng::from_seed(&[seed]);
		
		Map { seed: seed,
			  width: rng.gen_range(200u32, 1000u32),
			  height: rng.gen_range(200u32, 1000u32),
			}
	}
	
	//from_seed
	
	//from_config
	
	
}
