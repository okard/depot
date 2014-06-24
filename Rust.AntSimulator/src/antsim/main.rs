
extern crate antcore;

use ac = antcore;



fn main()
{
	let mut sim = ac::Simulator::new();
	
	let mut ai_one = ac::basicai::BaseAI::new(&sim as &ac::interface::HiveInterface);
	sim.add_colony(&mut ai_one);
	
	//let mut ai_one = ac::basicai::BaseAI::new(&sim);
	
	//add 2 base ais
	
	
	//create a renderer
}
