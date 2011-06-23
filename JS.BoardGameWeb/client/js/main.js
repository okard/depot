/*
 BoardGame Web Client
 Main Script File
 Licensed under GPLv3
 Author: okard
*/

//global states?

/**
* Initializer Function
*/
$(document).ready(function() {
   //hide no script box
   $("#noscript").hide(); 
   
   include("js/jquery.urldecoder.min.js");
   include("js/sjcl.js");
   
});


/**
* login user into the server
*/
function login()
{
    alert("login:" + $("#txtUsername").attr("value"));
    
    var srv = $("#cmbServer").attr("value");
    
    
    //connect to server (ssl!)
    
    //get seed from server?
    //hash(username) 
    //hash(pw+seed),seed
    
    //session cookie?
    
    $("#loginWindow").hide();
    $("#lobbyWindow").show();
    $("#statusBar").show();
}

/**
* logout
*/
function logout()
{
    alert("logout");
    $("#loginWindow").show();
    $("#lobbyWindow").hide();
    $("#statusBar").hide();
    $("#gameWindow").hide();
}
