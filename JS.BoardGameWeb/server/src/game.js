/*
 BoardGame Web Server
 Game Resource
 Licensed under GPLv3
 Author: okard
*/

//Imports
var util = require('./util.js');
var session = require('./session.js');

/**
* Http '/game' Handler
*/
exports.handler = function(req, url, res)
{
    session.start(req, res);
    
    //validate session
    console.log(session.get(req, 'userid') ? "authorized" : "not authorized");
    
    util.sendJson("game_handler");
}