

#![crate_id = "antcore#0.1"]
#![crate_type = "lib"]

#![allow(dead_code)]

//exports
pub use self::colony::{Colony};
pub use self::ant::{AntEntity};
pub use self::hill::{Hill};
pub use self::entity::{EntityType, Entity};
pub use self::map::{Map};
pub use self::action::{Action};
pub use self::simulator::{Simulator};

mod colony;
mod ant;
mod hill;
mod entity;
mod map;
mod action;

pub mod interface;
mod simulator;



pub mod basicai;




