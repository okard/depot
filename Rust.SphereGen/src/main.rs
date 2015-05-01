
extern crate toml;
extern crate rand;

use std::fs::File;
use std::io::Read;
use std::io::Write;

use rand::Rng;
use rand::os::OsRng;


struct Point
{
	x: f32,
	y: f32,
	z: f32
}


fn main()
{
	let mut conf_file = File::open("spheregen.config.toml").unwrap();

	let mut conf_content = "".to_string();
	conf_file.read_to_string(&mut conf_content).unwrap();
	let config: toml::Value = conf_content.parse().unwrap();
	
	let count = config.lookup("general.count").unwrap().as_integer().unwrap();
	
	let x_min = config.lookup("x.min").unwrap().as_integer().unwrap();
	let x_max = config.lookup("x.max").unwrap().as_integer().unwrap();
	
	let y_min = config.lookup("y.min").unwrap().as_integer().unwrap();
	let y_max = config.lookup("y.max").unwrap().as_integer().unwrap();
	
	let z_min = config.lookup("z.min").unwrap().as_integer().unwrap();
	let z_max = config.lookup("z.max").unwrap().as_integer().unwrap();
	
	let mut rnd = OsRng::new().unwrap();
	
	
	let mut outfile = File::create("output.csv").unwrap();
	
	for _ in 0..count
	{
		let x = rnd.gen_range(x_min, x_max);
		let y = rnd.gen_range(y_min, y_max);
		let z = rnd.gen_range(z_min, z_max);
		
		write!(&mut outfile, "{}, {}, {}\n", x, y, z);
	}
}
