/*
 BoardGame Web Client
 Server API
 Licensed under GPLv3
 Author: okard
*/

var api = 
{
    /**
    * Initialize Server API
    */
    init: function(srv)
    {
        this.server = srv;
        
        //check for crypto
        //check for jquery
    },
    
    
    /**
    * Login into Server
    */
    login: function(username, password)
    {   
        //basic json object for request
        //only map url path & parameters
        //server + /user/login
        
        //prepare pw
        password = sjcl.codec.hex.fromBits(this.hashPw(password));
        
        //send request
        $.getJSON(this.server + "user/login" + "?callback=?",
                  {
                    user: username,
                    password: password
                  },
                  function(data, textStatus, jqXHR) 
                  {
                      alert(data);
                  }
        ); 
    },
    
    
    /**
    * Private: Create a Request object
    */
    _createRequestObject: function()
    {
        var obj =  {
            url: this.server,
            contentType: "application/json",
            dataType: "json",
            type: "GET",
            context: this,
            statusCode: {
                404: function() { alert('page not found');},
                403: function() { alert('access denied'); }
            },
            error: function(jqXHR, textStatus, errorThrown){ alert("Error loading: " + textStatus + " " + errorThrown);}
        };
        
        return obj; 
    },
    
    /**
    * Hash PW
    */
    hashPw: function(pw)
    {
        for (var i=0;i<=256;i++)
        {
            pw = sjcl.hash.sha256.hash(pw);
        }
        return pw; 
    }
      
};