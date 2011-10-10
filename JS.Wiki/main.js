

var http = require('http');


///////////////////////////////////////////////////
//backend
var config =
{
}

var backend = require('./srv/server.js');
var bsrv = new(backend.Server)(config);
http.createServer(bsrv.handler).listen(56000, "127.0.0.1");


///////////////////////////////////////////////////
//frontend
var static = require('./lib/node-static.js');
var file = new(static.Server)('./web');

http.createServer(function (request, response) 
{
  request.addListener('end', function () {
    file.serve(request, response);
  });
}).listen(8080, "127.0.0.1");



