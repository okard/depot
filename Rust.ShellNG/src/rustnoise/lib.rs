
#![crate_id = "rustnoise"]
#![crate_type = "lib"]

#[allow(dead_code)]

extern crate libc;
use std::c_str::{CString};

#[allow(non_camel_case_types)]
pub struct Struct_linenoiseCompletions {
    pub len: ::libc::size_t,
    pub cvec: *mut *mut ::libc::c_char,
}

#[allow(non_camel_case_types)]
pub type linenoiseCompletions = Struct_linenoiseCompletions;
#[allow(non_camel_case_types)]
pub type linenoiseCompletionCallback = ::libc::c_void;

#[link(name = "linenoise", kind = "static")]
extern "C" {
    pub fn linenoiseSetCompletionCallback(arg1: *mut linenoiseCompletionCallback);
    pub fn linenoiseAddCompletion(arg1: *mut linenoiseCompletions,
                                  arg2: *::libc::c_char);
                                  
    
    pub fn linenoise(prompt: *::libc::c_char) -> *mut ::libc::c_char;
    
    pub fn linenoiseHistoryAdd(line: *::libc::c_char) -> ::libc::c_int;
    pub fn linenoiseHistorySetMaxLen(len: ::libc::c_int) -> ::libc::c_int;
    pub fn linenoiseHistorySave(filename: *::libc::c_char) -> ::libc::c_int;
    pub fn linenoiseHistoryLoad(filename: *::libc::c_char) -> ::libc::c_int;
    pub fn linenoiseClearScreen();
    pub fn linenoiseSetMultiLine(ml: ::libc::c_int);
    pub fn linenoisePrintKeyCodes();
}

pub fn rustnoise(prompt: &str) -> CString
{
	unsafe {
		CString::new(linenoise(prompt.as_bytes().as_ptr() as *::libc::c_char) as *::libc::c_char, true)
	}
}


