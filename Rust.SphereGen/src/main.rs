
extern crate toml;
extern crate rand;

use std::fs::File;
use std::io::Read;
use std::io::Write;

use rand::Rng;
use rand::os::OsRng;


fn main()
{
	//when arguments available use first one for config file
	let mut conf_file = File::open("spheregen.config.toml").unwrap();

	let mut conf_content = "".to_string();
	conf_file.read_to_string(&mut conf_content).unwrap();
	let config: toml::Value = conf_content.parse().unwrap();
	
	let segments = config.lookup("segment").unwrap().as_slice().unwrap();
	println!("{} Segments", segments.len());
	
	let mut outfile = File::create("output.csv").unwrap();
	
	let mut i = 0;
	for segment in segments
	{
		println!("Do segment {}", i);
		do_segment(&mut outfile, &segment);
		i += 1;
	}
}


fn do_segment(output: &mut Write, segment: &toml::Value)
{
	let mut rnd = OsRng::new().unwrap();
	let count = segment.lookup("count").unwrap().as_integer().unwrap();
	
	let x_start = segment.lookup("x_start").unwrap().as_integer().unwrap();
	let x_distance = segment.lookup("x_distance").unwrap().as_integer().unwrap();
	let x_end = segment.lookup("x_end").unwrap().as_integer().unwrap();

	let y_start = segment.lookup("y_start").unwrap().as_integer().unwrap();
	let y_distance = segment.lookup("y_distance").unwrap().as_integer().unwrap();
	let y_end = segment.lookup("y_end").unwrap().as_integer().unwrap();
	
	let z_start = segment.lookup("z_start").unwrap().as_integer().unwrap();
	let z_distance = segment.lookup("z_distance").unwrap().as_integer().unwrap();
	let z_end = segment.lookup("z_end").unwrap().as_integer().unwrap();
	
	
	//check stuff
	
	//calculate points
	let mut i = 0;
	while i < count
	{
		let x = rnd.gen_range(x_start, x_end);
		let y = rnd.gen_range(y_start, y_end);
		let z = rnd.gen_range(z_start, z_end);
		
		let a = (if x >= 0 {x_end} else {x_start}).abs();
		let b = (if x >= 0 {y_end} else {y_start}).abs();
		let c = (if x >= 0 {z_end} else {z_start}).abs();
		
		//check for x,y,z negative or not to choose the right a,b,c distance 
		//(x/a)^2 + (y/b)^2 + (z/c)^2 = 1
		//if it's less than 1, the point is inside the ellipsoid.
		
		//check if not inside of outer ellipsoid 
		if (x/a).pow(2) + (y/b).pow(2) + (z/c).pow(2) >= 1 {
			continue;
		}
		
		//check if its outside the inner ellipsoid
		if x_distance > 0 && y_distance > 0 && z_distance > 0
		&& (x/x_distance).pow(2) + (y/y_distance).pow(2) + (z/z_distance).pow(2) <= 1 {
			continue;
		}
		
		//let mut output = &mut output;
		write!(output, "{}, {}, {}\n", x, y, z);
		i += 1;
	}
}
