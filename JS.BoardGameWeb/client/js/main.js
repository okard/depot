/*
 BoardGame Web
 Main Script File
 Licensed under GPLv3
 Author: okard
*/

/**
* Initializer Function
*/
$(document).ready(function() {
   //hide no script box
   $("#noscript").hide(); 
    
});


/**
* login user into the server
*/
function login()
{
    alert("login:" + $("#txtUsername").attr("value"));
    
    //connect to server (ssl!)
    
    //get seed from server?
    //hash(username) 
    //hash(pw+seed),seed
    
    //session cookie?
    
}