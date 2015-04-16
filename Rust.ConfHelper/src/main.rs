/*

source_dir is the repository of files
local_dir is the working directory

*/
#![feature(convert)]
#![feature(path_relative_from)]
#![feature(fs_time)]
#![feature(path_ext)]

extern crate toml; 
extern crate crypto;
extern crate argparse;

use std::os;
use std::io;
use std::env;
use std::fs;
use std::str;

use std::path::{PathBuf, Path};
use std::fs::PathExt;
use std::io::{Read};

use argparse::{ArgumentParser, StoreTrue, Store};

//get config path
//get config_settings

/**
* Search and load the config
*/
fn get_config() -> Option<toml::Table> //result
{
	//search for config
	//os::homedir() -> Option<Path>
	//os::self_exe_path()
	//
	
	
	let conf_file = env::home_dir().unwrap().join(".config/confhelper.config.toml");
	if conf_file.is_file() {
		println!("Config-File: {}", conf_file.display());
		
		let mut content : Vec<u8> = Vec::new();
		fs::File::open(&conf_file).unwrap().read_to_end(&mut content);
		
		let config = toml::Parser::new(str::from_utf8(content.as_slice()).unwrap()).parse().unwrap();
		return Some(config);
	}
	
	None
}

/**
* try to convert a path to an absolute path
*/
fn get_absolute_path(path : &str) -> Option<PathBuf>
{
	let path = path.replace("~", env::home_dir().unwrap().to_str().unwrap());
	let path = PathBuf::from(path);
	
	//println!("absolute for: {}", path.display());
	//println!("path '{}' is_dir {}", path.display(), path.is_dir());
	
	//is directly accessable make it full path
	if (path.is_dir() || path.is_file()) && !path.is_absolute() {
		let cwd = env::current_dir().unwrap();
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

/**
* create sha1sum of a file
*/
fn sha1sum(file: &Path) -> Vec<u8>
{
	use crypto::digest::Digest;
	let mut sha = crypto::sha1::Sha1::new();
	//TODO chunk reading
	
	let mut content : Vec<u8> = Vec::new();
	fs::File::open(&file).unwrap().read_to_end(&mut content);
	sha.input(content.as_slice());
	let mut out = [0u8; 20];
	sha.result(&mut out);
	return out.to_vec();
}

/**
* compare two files (part of diff command)
*/
fn compare_files(local_file : &Path, source_file: &Path)
{
	//create sha1 sums
	let local_checksum = sha1sum(local_file);
	let source_checksum = sha1sum(source_file);
	
	if local_checksum == source_checksum {
		println!("Checksum of both file are identical");
		return;
	}
	
	let local_file_meta = local_file.metadata().unwrap();
	let source_file_meta = source_file.metadata().unwrap();
	
	//if differs check modified date
	if local_file_meta.modified() < source_file_meta.modified() {
		//<local> <source>/
		println!("{} is newer than {}", source_file.display(), local_file.display());
	}
	
	if local_file_meta.modified() > source_file_meta.modified() {
		println!("{} is newer than {}", local_file.display(), source_file.display());
	}
	
	if local_file_meta.modified() == source_file_meta.modified() {
		println!("{} seems identical {}", local_file.display(), source_file.display());
	}
	
	//call diff command?
}


// fn get_file_pair(file_to_check, local_dir, source_dir) -> Option<(Path,Path)>

/**
* Implement the diff command
*/
fn diff_command(verbose: bool, file_to_check: &str, local_dir: &Path, source_dir: &Path)
{
	assert!(local_dir.is_absolute());
	assert!(source_dir.is_absolute());
	
	//get the absolute path to current file
	let file_to_check = get_absolute_path(file_to_check);
	
	if file_to_check.is_none() {
		println!("file not found");
		return;
	}
	let file_to_check = file_to_check.unwrap();
	
	if verbose {
		println!("File-to-check: {}", file_to_check.display());
	}
	
	//find matching file
	let local_file;
	let source_file;
	
	//set source and local file
	match (file_to_check.starts_with(&local_dir), file_to_check.starts_with(&source_dir)) 
	{
		(true, true) => {
			//source dir is in local and file is in source_dir
			if local_dir.starts_with(source_dir) {
				//file is in source
				source_file = file_to_check.clone();
				local_file = local_dir.join(file_to_check.relative_from(source_dir).unwrap());
			}
			else //use local dir for file 
			{
				source_file = source_dir.join(file_to_check.relative_from(local_dir).unwrap());
				local_file = file_to_check.clone(); 
			}
		} //use source as base
		(false, true) => { 
			//only in source
			source_file = file_to_check.clone();
			local_file = local_dir.join(file_to_check.relative_from(source_dir).unwrap());
			
		} //use source as base
		(true, false) => { 
			source_file = source_dir.join(file_to_check.relative_from(local_dir).unwrap());
			local_file = file_to_check.clone(); 
		} //use local as base
		(false, false) => { 
			//create? where to create?
			println!( "the file is not in local or source dir"); 
			return;
		} 
	}
	
	if verbose {
		println!("Local-File: {}", local_file.display());
		println!("Source-File: {}", source_file.display());
	}
	
	compare_files(&local_file, &source_file);
	
	//source_file, local_file
	//local does not exist
	//source does not exist
	//local and source are identical
	//local is newer
	//source is newer
	
	//find file in local or source dir
	
	//actions: 
}




fn main()
{
	let mut verbose: bool = false;
	let mut config_file = "".to_string();
	let mut command = "".to_string();
	let mut filename = "".to_string();
	{  
		let mut ap = ArgumentParser::new();
		ap.set_description("Conf Helper");
		ap.refer(&mut verbose).add_option(&["-v", "--verbose"], StoreTrue, "Be verbose");
		ap.refer(&mut config_file).add_option(&["-c", "--config"], Store, "Use following config file");
		ap.refer(&mut command).add_argument("command", Store, "Command to run");
		ap.refer(&mut filename).add_argument("filename", Store, "filename");
		ap.parse_args_or_exit();
	}
	if command.is_empty() 
	|| filename.is_empty()
	{
		println!("Missing arguments use -h or --help for more information");
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
	assert!(config.contains_key(&"local".to_string()));
	assert!(config.contains_key(&"source".to_string()));
	
	//load local dir
	let local_dir = get_absolute_path(config.get(&"local".to_string()).unwrap().as_str().unwrap());
	if local_dir.is_none() {
		println!("local_dir not available");
		return;
	}
	let local_dir = local_dir.unwrap();
	
	//load source dir
	let source_dir = get_absolute_path(config.get(&"source".to_string()).unwrap().as_str().unwrap());
	if source_dir.is_none() {
		println!("source_dir not available");
		return;
	}
	let source_dir = source_dir.unwrap();
	
	if(verbose)
	{
		println!("Config-Content: {:?}", config);
		println!("Source-Dir: {:?}", source_dir);
		println!("Local-Dir: {:?}", local_dir);
	}
	
	//when source is in local source has to be longer than local
	//check which path is longer
	if !source_dir.starts_with(&local_dir) {
		println!("source dir has to be longer than local dir");
		return;
	}
	
	//find the specific file stuff before looking at command?
	
	
	//look for command
	match command.as_str()
	{
		//compares a file 
		"diff" => { diff_command(verbose, filename.as_str(), &local_dir, &source_dir); }
		
		//push file from local to source?
		"push" => { } //only local files? or source->local|local->source
		//replace a local file with the source file
		"pop" => { /* */ } 
		//try to merge both files in local (push afterwards if wanted)
		"merge" => {}
		
		//loop through source directory and compare all files
		//"check_all" 
		
		_ => { println!("Invalid Command"); }
	}
	
	
	//look if it is the source or local dir 
		//attention when using starts with it is the better match
		//get the right other file
		
	//start comparing
	//copying / replacement
	//merging
	
	//let value = toml::Parser::new(toml).parse().unwrap();
}
