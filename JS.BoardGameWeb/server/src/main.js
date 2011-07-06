/*
 BoardGame Web Server
 Main Script File
 Licensed under GPLv3
 Author: okard
*/

var https = require('https');
var fs = require('fs');
var url = require('url');

var config = require('./config.js').config;
var handler = require('./handler.js');
var util = require('./util.js');

//ssl options
var options = {
    key: fs.readFileSync(config.http_ssl_key),
    cert: fs.readFileSync(config.http_ssl_cert)
};

// handler urls
var handler = {
    "/game" : handler.game,
    "/lobby" : handler.lobby,
    "/user" : handler.user
};


//create a https server
https.createServer(options, function (req, res) 
{
    var u = url.parse(req.url);
    
    //u.pathname = u.pathname.split('/');
    //console.log(u.pathname);
   
    //parse req 
    console.log('Request: ' + req.url + ' method: ' + req.method + ' headers: ' + JSON.stringify(req.headers));
    console.log('Cookies: ' + JSON.stringify(util.cookies(req)));
    
    
    for(h in handler)
    {
        //look for right handler (hashtable for js?)
        if(util.startsWith(u.pathname, h))
        {
            u.pathname = u.pathname.substr(1).split('/');
            handler[h](req, u, res);
            console.log("\n\n");
            return;
        }
        
    }
    
    //send not found here
    util.send404(req, res);
  
}).listen(53001, "127.0.0.1");

console.log('Server running');


/*
    REST API:
    
    user/login
    user/logout

    lobby/

        id=gameid
    game/create[POST]
    game/join/
    
    game/notation[GET]  format="json", "text"

*/