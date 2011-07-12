/*
 BoardGame Web Server
 Lobby Resource
 Licensed under GPLv3
 Author: okard
*/

//Imports
var util = require('./util.js');
var session = require('./session.js');

/**
* Http '/lobby' Handler
*/
exports.handler = function(req, url, res)
{
    util.sendJson("lobby_handler");
}