/*

source_dir is the repository of files
target_dir is the working directory

*/
extern crate toml; 
extern crate "rust-crypto" as crypto;

use std::os;
use std::path::Path;
use std::io::fs::PathExtensions;
use std::io;

/**
* Search and load the config
*/
fn get_config() -> Option<toml::TomlTable>
{
	//search for config
	//os::homedir() -> Option<Path>
	//os::self_exe_path()
	//
	
	
	let conf_file = os::homedir().unwrap().join(".config/confhelper.config.toml");
	if conf_file.is_file() {
		println!("Config-File: {}", conf_file.display());
		
		let contents = io::File::open(&conf_file).read_to_end();
		let contents = String::from_utf8(contents.ok().unwrap()).ok().unwrap();
		let config = toml::Parser::new(contents.as_slice()).parse().unwrap();
		return Some(config);
	}
	
	None
}

/**
* try to convert a path to an absolute path
*/
fn get_absolute_path(path : &str) -> Option<Path>
{
	let path = path.replace("~", os::homedir().unwrap().as_str().unwrap());
	let path = Path::new(path);
	
	//println!("absolute for: {}", path.display());
	//println!("path '{}' is_dir {}", path.display(), path.is_dir());
	
	//is directly accessable make it full path
	if (path.is_dir() || path.is_file()) && !path.is_absolute() {
		let cwd = os::getcwd();
		let path = cwd.join(path);
		
		assert!(path.is_dir() || path.is_file());
		assert!(path.is_absolute());
		
		return Some(path);
	}	
	
	//already a absolute path
	if (path.is_dir() || path.is_file()) && path.is_absolute() {
		return Some(path);
	}
	
	//does not exist or is a directoy
	return None;
}


fn sha1sum(file: &Path) -> Vec<u8>
{
	use crypto::digest::Digest;
	let mut sha = crypto::sha1::Sha1::new();
	//TODO chunk reading
	let contents = io::File::open(file).read_to_end().unwrap();
	sha.input(contents.as_slice());
	let mut out = [0u8, ..20];
	sha.result(out);
	return out.to_vec();
}

fn compare_files(target_file : &Path, source_file: &Path)
{
	//create sha1 sums
	let target_checksum = sha1sum(target_file);
	let source_checksum = sha1sum(source_file);
	
	if target_checksum == source_checksum {
		println!("Checksum of both file are identical");
		return;
	}
	
	let target_file_stat = target_file.lstat().unwrap();
	let source_file_stat = source_file.lstat().unwrap();
	
	//if differs check modified date
	if target_file_stat.modified < source_file_stat.modified {
		//<target> <source>/
		println!("{} is newer than {}", source_file.display(), target_file.display());
	}
	
	if target_file_stat.modified > source_file_stat.modified {
		println!("{} is newer than {}", target_file.display(), source_file.display());
	}
	
	if target_file_stat.modified == source_file_stat.modified {
		println!("{} seems identical {}", target_file.display(), source_file.display());
	}
	
	//call diff command?
}


// fn get_file_pair(file_to_check, target_dir, source_dir) -> Option<(Path,Path)>

/**
* Implement the diff command
*/
fn diff_command(file_to_check: &str, target_dir: &Path, source_dir: &Path)
{
	//get the absolute path to current file
	let file_to_check = get_absolute_path(file_to_check);
	
	if file_to_check.is_none() {
		println!("file not found");
		return;
	}
	let file_to_check = file_to_check.unwrap();
	
	//find matching file
	let target_file;
	let source_file;
	
	//set source and target file
	match (target_dir.is_ancestor_of(&file_to_check), source_dir.is_ancestor_of(&file_to_check)) 
	{
		(true, true) => {
			//source dir is in target and file is in source_dir
			if target_dir.is_ancestor_of(source_dir) {
				//file is in source
				source_file = file_to_check.clone();
				target_file = target_dir.join(file_to_check.path_relative_from(source_dir).unwrap());
			}
			else //use target dir for file 
			{
				source_file = source_dir.join(file_to_check.path_relative_from(target_dir).unwrap());
				target_file = file_to_check.clone(); 
			}
		} //use source as base
		(false, true) => { 
			//only in source
			source_file = file_to_check.clone();
			target_file = target_dir.join(file_to_check.path_relative_from(source_dir).unwrap());
			
		} //use source as base
		(true, false) => { 
			source_file = source_dir.join(file_to_check.path_relative_from(target_dir).unwrap());
			target_file = file_to_check.clone(); 
		} //use target as base
		(false, false) => { 
			//create? where to create?
			println!( "the file is not in target or source dir"); 
			return;
		} 
	}
	
	println!("target_file: {}", target_file.display());
	println!("source_file: {}", source_file.display());
	
	compare_files(&target_file, &source_file);
	
	//source_file, target_file
	//target does not exist
	//source does not exist
	//target and source are identical
	//target is newer
	//source is newer
	
	//find file in target or source dir
	
	//actions: 
}




fn main()
{
	let args = os::args();
	
	//todo --verbose flag
	
	//look for arguments
	if args.len() < 3 {
		println!("Missing arguments");
		return;
	}
	
	//get config
	let config = get_config();
	if config.is_none() {
		println!("Missing config");
		return;
	}
	let config = config.unwrap();
	
	//validate config?
	assert!(config.contains_key(&"target".to_string()));
	assert!(config.contains_key(&"source".to_string()));
	
	//load target dir
	let target_dir = get_absolute_path(config.get(&"target".to_string()).unwrap().as_str().unwrap());
	if target_dir.is_none() {
		println!("target_dir not available");
		return;
	}
	let target_dir = target_dir.unwrap();
	
	//load source dir
	let source_dir = get_absolute_path(config.get(&"source".to_string()).unwrap().as_str().unwrap());
	if source_dir.is_none() {
		println!("source_dir not available");
		return;
	}
	let source_dir = source_dir.unwrap();
	
	
	//when source is in target source has to be longer than target
	//check which path is longer
	if source_dir.is_ancestor_of(&target_dir) {
		println!("source dir has to be longer than target dir");
		return;
	}
	
	//config seems to be valid at this point
	
	println!("Config-Content: {}", config);
	
	//find the specific file stuff before looking at command?
	
	
	//look for command
	let command = args[1].as_slice();
	match command 
	{
		//compares a file 
		"diff" => { diff_command(args[2].as_slice(), &target_dir, &source_dir); }
		
		//push file from target to source?
		"push" => { } //only target files? or source->target|target->source
		//replace a target file with the source file
		"pop" => { /* */ } 
		//try to merge both files in target (push afterwards if wanted)
		"merge" => {}
		
		//loop through source directory and compare all files
		//"check_all" 
		
		_ => { println!("Invalid Command"); }
	}
	
	
	//look if it is the source or target dir 
		//attention when using starts with it is the better match
		//get the right other file
		
	//start comparing
	//copying / replacement
	//merging
	
	//let value = toml::Parser::new(toml).parse().unwrap();
}
