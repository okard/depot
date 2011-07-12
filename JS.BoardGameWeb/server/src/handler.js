/*
 BoardGame Web Server
 Http Handler
 Licensed under GPLv3
 Author: okard
*/

var util = require('./util.js');
var session = require('./session.js');

/**
* Game Handler
* Handle Game Functions, do moves, etc
*/ 
function game_handler(req, url, res)
{   
    session.start(req, res);
    
    //validate session
    console.log(session.get(req, 'userid') ? "authorized" : "not authorized");
    
    util.sendJson("game_handler");
}

/**
* Lobby Handler
* Handle Lobby Functions, Messaging ,etc
*/
function lobby_handler(req, url, res)
{
    util.sendJson("lobby_handler");
}

//export functions
exports.game = game_handler; 
exports.lobby = lobby_handler;