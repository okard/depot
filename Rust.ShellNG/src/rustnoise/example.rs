

extern crate rustnoise;

fn main()
{	
	loop {
		let line = rustnoise::rustnoise("> ");
		
		if line.is_null() {
			break;
		}
		
		println!("{}", line.as_str().get_ref());
	}
	
}
