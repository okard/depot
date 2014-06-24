
pub enum LoadType {
	None,
	Food,
	Wood
}

pub struct AntLoad {
	typ: LoadType,
	amount: u32
}

pub struct AntEntity {
	colonyId: u32,
	categoryId: u32,		//helper for ai to define roles (stats) of ant
	livepoints: u32,
	energy: u32,
	livepoint: u32,
	strength: u32,
	attack: u32,
	attackrange: u32, 
	workpower: u32,
	senserange: u32,
	speed: f32,
	absorbspeed: f32,
	
	//load
	load: AntLoad,
	
	dataId: u32, //can be used as behavior id or task id or instance id
	
	//position
}

impl AntEntity 
{
	pub fn new()  -> AntEntity
	{
		AntEntity {
			colonyId: 0,
			categoryId: 0,		//helper for ai to define roles (stats) of ant
			livepoints: 0,
			energy: 0,
			livepoint: 0,
			strength: 0,
			attack: 0,
			attackrange: 0, 
			workpower: 0,
			senserange: 0,
			speed: 0f32,
			absorbspeed: 0f32,
			
			//load
			load: AntLoad {typ: None, amount:0 },
			
			dataId: 0,
		}
	}
}
