
extern crate toml;
extern crate rand;

use std::fs::File;
use std::io::Read;
use std::io::Write;
use std::f32::consts::PI;
use std::ops::Neg;

use rand::Rng;
use rand::os::OsRng;


fn main()
{
	let mut config_file_string = "spheregen.config.toml".to_string();
	let mut args = std::env::args();
	if args.len() == 2 {
		config_file_string = args.nth(1).unwrap();
	}
	
	//when arguments available use first one for config file
	let mut conf_file = File::open(config_file_string).unwrap();

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
	
	//read in config
	let mut count = segment.lookup("count").unwrap().as_integer().unwrap();
	let density = segment.lookup("density").unwrap().as_float().unwrap();
	
	let x_start = segment.lookup("x_start").unwrap().as_integer().unwrap().abs();
	let x_start_min = segment.lookup("x_start_min").unwrap().as_integer().unwrap().abs();
	let x_end_min = segment.lookup("x_end_min").unwrap().as_integer().unwrap().abs();
	let x_end = segment.lookup("x_end").unwrap().as_integer().unwrap().abs();

	let y_start = segment.lookup("y_start").unwrap().as_integer().unwrap().abs();
	let y_start_min = segment.lookup("y_start_min").unwrap().as_integer().unwrap().abs();
	let y_end_min = segment.lookup("y_end_min").unwrap().as_integer().unwrap().abs();
	let y_end = segment.lookup("y_end").unwrap().as_integer().unwrap().abs();
	
	let z_start = segment.lookup("z_start").unwrap().as_integer().unwrap().abs();
	let z_start_min = segment.lookup("z_start_min").unwrap().as_integer().unwrap().abs();
	let z_end_min = segment.lookup("z_end_min").unwrap().as_integer().unwrap().abs();
	let z_end = segment.lookup("z_end").unwrap().as_integer().unwrap().abs();
	
	//check stuff
	
	//calculate volume V=3/4*pi*a*b*c
	//8 sides
	
	//front
	//  xyz
	let ppp = ((3f32/4f32*PI*x_end as f32*y_end as f32*z_end as f32)/8f32) 
			- ((3f32/4f32*PI*x_end_min as f32*y_end_min as f32*z_end_min as f32)/8f32);
	let pnp = ((3f32/4f32*PI*x_end as f32*y_start as f32*z_end as f32)/8f32) 
			- ((3f32/4f32*PI*x_end_min as f32*y_start_min as f32*z_end_min as f32)/8f32);
	let nnp = ((3f32/4f32*PI*x_start as f32*y_start as f32*z_end as f32)/8f32) 
			- ((3f32/4f32*PI*x_start_min as f32*y_start_min as f32*z_end_min as f32)/8f32);
	let npp = ((3f32/4f32*PI*x_start as f32*y_end as f32*z_end as f32)/8f32) 
			- ((3f32/4f32*PI*x_start_min as f32*y_end_min as f32*z_end_min as f32)/8f32);
	//back
	let ppn = ((3f32/4f32*PI*x_end as f32*y_end as f32*z_start as f32)/8f32) 
			- ((3f32/4f32*PI*x_end_min as f32*y_end_min as f32*z_start_min as f32)/8f32);
	let pnn = ((3f32/4f32*PI*x_end as f32*y_start as f32*z_start as f32)/8f32) 
			- ((3f32/4f32*PI*x_end_min as f32*y_start_min as f32*z_start_min as f32)/8f32);
	let nnn = ((3f32/4f32*PI*x_start as f32*y_start as f32*z_start as f32)/8f32) 
			- ((3f32/4f32*PI*x_start_min as f32*y_start_min as f32*z_start_min as f32)/8f32);
	let npn = ((3f32/4f32*PI*x_start as f32*y_end as f32*z_start as f32)/8f32) 
			- ((3f32/4f32*PI*x_start_min as f32*y_end_min as f32*z_start_min as f32)/8f32);
	
	let volume = ppp+pnp+nnp+npp
			   + ppn+pnn+nnn+npn;
	
	if density > 0f64 {
		count = (density * volume as f64).floor() as i64;
	}
	
	println!("Count: {}; Volume of segment: {}", count, volume);
	
	//calculate points
	let mut i = 0;
	while i < count
	{
		let x = rnd.gen_range(x_start.neg(), x_end);
		let y = rnd.gen_range(y_start.neg(), y_end);
		let z = rnd.gen_range(z_start.neg(), z_end);
		
		//outer ellipsoid
		let a = if x >= 0 {x_end} else {x_start};
		let b = if x >= 0 {y_end} else {y_start};
		let c = if x >= 0 {z_end} else {z_start};
		
		//inner ellipsoid
		let a_inner = if x >= 0 {x_end_min} else {x_start_min};
		let b_inner = if x >= 0 {y_end_min} else {y_start_min};
		let c_inner = if x >= 0 {z_end_min} else {z_start_min};
		
		//check for x,y,z negative or not to choose the right a,b,c distance 
		//(x/a)^2 + (y/b)^2 + (z/c)^2 = 1
		//if it's less than 1, the point is inside the ellipsoid.
		
		//check if not inside of outer ellipsoid 
		if (x/a).pow(2) + (y/b).pow(2) + (z/c).pow(2) >= 1 {
			continue;
		}
		
		//check if its not in the inside the inner ellipsoid
		if a_inner > 0 
		&& b_inner > 0 
		&& c_inner > 0
		&& (x/a_inner).pow(2) + (y/b_inner).pow(2) + (z/c_inner).pow(2) <= 1 {
			continue;
		}
		
		//let mut output = &mut output;
		write!(output, "{}, {}, {}\n", x, y, z);
		i += 1;
	}
}
