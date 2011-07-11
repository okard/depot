/*
 BoardGame Web Client
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
   
   //load library scripts
   include("js/jquery.urldecoder.min.js");
   include("js/jquery.cookie.js");
   include("js/sjcl.js");
   include("js/api.js");
   
   
   //look which state user is and switch to right page  
});


/**
* login user into the server
*/
function login()
{   
    var user = $("#txtUsername").attr("value");
    var pw = $("#txtPassword").attr("value");
    var server = $("#cmbServer").attr("value");
    
    //initialize Server API
    api.init(server);
    
    //login to server
    api.login(user, pw);
    
    //handle error/success
    
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
