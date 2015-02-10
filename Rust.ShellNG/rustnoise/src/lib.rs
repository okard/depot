
#![crate_name = "rustnoise"]
#![crate_type = "lib"]

#[allow(dead_code)]

extern crate libc;
use std::ffi::{CString};
use std::str::{from_c_str};
use libc::funcs::c95::stdlib::{free};

#[allow(non_camel_case_types)]
#[repr(C)]
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
                                  arg2: *const ::libc::c_char);
                                  
    
    pub fn linenoise(prompt: *const ::libc::c_char) -> *mut ::libc::c_char;
    
    pub fn linenoiseHistoryAdd(line: *const ::libc::c_char) -> ::libc::c_int;
    pub fn linenoiseHistorySetMaxLen(len: ::libc::c_int) -> ::libc::c_int;
    pub fn linenoiseHistorySave(filename: *const ::libc::c_char) -> ::libc::c_int;
    pub fn linenoiseHistoryLoad(filename: *const ::libc::c_char) -> ::libc::c_int;
    pub fn linenoiseClearScreen();
    pub fn linenoiseSetMultiLine(ml: ::libc::c_int);
    pub fn linenoisePrintKeyCodes();
}

pub fn rustnoise(prompt: &str) -> CString
{
	unsafe {
		let line = linenoise(prompt.as_bytes().as_ptr() as *const ::libc::c_char);
		let cstring = CString::from_slice(from_c_str(line).as_bytes());
		free(line as *mut libc::types::common::c95::c_void);
		return cstring;
	}
}

pub fn rustnoise_history_add(line: &str) 
{
	unsafe {
		linenoiseHistoryAdd(line.as_bytes().as_ptr() as *const ::libc::c_char);
	}
}

pub fn rustnoise_history_setlen(len: i32) 
{
	unsafe {
		linenoiseHistorySetMaxLen(len);
	}
}


