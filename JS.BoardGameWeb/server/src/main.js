/*
 BoardGame Web Server
 Main Script File
 Licensed under GPLv3
 Author: okard
*/

var https = require('https');
var fs = require('fs');

var config = require('./config.js').config;

//test certs -> config
var options = {
  key: fs.readFileSync(config.http_ssl_key),
  cert: fs.readFileSync(config.http_ssl_cert)
};


//create a https server
https.createServer(options, function (req, res) 
{
    //parse req 
    console.log('Request: ' + req.url + ' method: ' + req.method);
    
    res.writeHead(200, {'Content-Type': 'text/plain'});
    res.end('Hello World\n');
  
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