
use ant::{AntEntity};


pub enum EntityType {
	AntType,
	Food,
	Wood,
}


pub enum Entity {
	//Ant
	Ant(Box<AntEntity>),
	
	//insects/creatures:
	Maggot,
	Beetle,
	
	//
	Stick,
	SugarPiece,
	Apple,
} 
