/*
 BoardGame Web Server
 Utils
 Licensed under GPLv3
 Author: okard
*/


var assert = require('assert');

/**
* String starts with
*/
exports.startsWith = function(str, match)
{
    assert.equal(typeof(str), "string", "Parameter str must be string");
    assert.equal(typeof(match), "string", "Parameter match must be string");
    
    return str.substr(0, match.length).indexOf(match) != -1;
}


/**
* Extract cookies from Request
*/
exports.cookies = function(req)
{
  var cookies = {};
  
  //extract cookies
  req.headers.cookie && req.headers.cookie.split(';').forEach(function( cookie ) {
    var parts = cookie.split('=');
    cookies[ parts[ 0 ].trim() ] = ( parts[ 1 ] || '' ).trim();
  });
  
  return cookies;

  // To Write a Cookie
  /*response.writeHead(200, {
    'Set-Cookie': 'mycookie=test',
    'Content-Type': 'text/plain'
  });*/
    
}

/**
* Get a random number between min and max
*/
exports.random_range = function(min, max)
{
    if( min > max ) {
        return( -1 );
    }
    if( min == max ) {
        return( min );
    }
 
    return( min + parseInt( Math.random() * ( max-min+1 ) ) );
}

/**
* Write a JSON Object to Response Stream
*/
exports.sendJson = function(res, obj)
{
    var header = {
        'Content-Type': 'application/json'
    }
    res.writeHead(200, header);
    res.end("(" + JSON.stringify(obj) + ")");    
}

/**
* Send a JSON Error Object
*/
exports.sendError = function(res, errorid, msg)
{
    exports.sendJson(res, {
        error: errorid,
        msg: msg,
        status: 'error'
    });
}

/**
* send a 404 error
* page not found
*/
exports.send404 = function (req, res)
{
    //TODO HTTP Errors with JSON as Return?
    
    res.writeHead(404, {'Content-Type': 'text/html'});
    res.write("<h1>404 Not Found</h1>");
    res.end("The page you were looking for: "+req.pathname+" can not be found");    
}

/**
* send a 403 error
* forbidden
*/
exports.send403 = function (req, res)
{
    res.writeHead(403, {'Content-Type': 'text/html'});
    res.write("<h1>403 Forbidden</h1>");
    res.end("Access to page: "+req.pathname+" is forbidden");     
}