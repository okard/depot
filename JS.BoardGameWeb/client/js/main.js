/*
 BoardGame Web Client
 Main Script File
 Licensed under GPLv3
 Author: okard
*/

//global states?
var server = "";

/**
* Initializer Function
*/
$(document).ready(function() {
   //hide no script box
   $("#noscript").hide(); 
   
   //load library scripts
   include("js/jquery.urldecoder.min.js");
   include("js/sjcl.js");
   
});


/**
* login user into the server
*/
function login()
{   
    var user = $("#txtUsername").attr("value");
    
    //256 rounds for pw hash
    var pwhash = $("#txtPassword").attr("value");
    for (var i=0;i<=256;i++)
    {
        pwhash = sjcl.hash.sha256.hash(pwhash);
    }
    
    
    alert("pwhash: " + sjcl.codec.hex.fromBits(pwhash));
    
    server = $("#cmbServer").attr("value");
    
    
    var response = null;
    
    //try to login into server
    $.ajax({
        url: "test.html",
        contentType: "application/json",
        dataType: "json",
        type: "POST",
        context: this,
        statusCode: {
                     404: function() { alert('page not found');},
                     403: function() { alert('access denied'); }
                    },
        success: function(){
                $(this).addClass("done");
            }
    });
    
    
    //error(jqXHR, textStatus, errorThrown)
    
    //connect to server (ssl!)
    
    //get seed from server?
    //hash(username)  100 x sha256
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
