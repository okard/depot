/*
 BoardGame Web Server
 Http Handler
 Licensed under GPLv3
 Author: okard
*/

var util = require('./util.js');

/**
* Game Handler
* Handle Game Functions, do moves, etc
*/ 
function game_handler(req, url, res)
{
    var str = "game_handler";
    
    //extract session id
    //validate session
    
    //actions
    //-create
    //-spectate
    //-move
    //-pick
    //-
    
    var header = {
        'Content-Type': 'application/json',
        'Set-Cookie': 'sessionid=test',
    }
    
    res.writeHead(200, header);
    res.end(JSON.stringify(str));    
}

/**
* Lobby Handler
* Handle Lobby Functions, Messaging ,etc
*/
function lobby_handler(req, url, res)
{
    res.writeHead(200, {'Content-Type': 'text/plain'});
    res.end('lobby_handler\n');
}

/**
* User Handler
* Handle Logins, Logouts, etc
*/
function user_handler(req, url, res)
{
    //login (session cookie) /game/login?user=abc&pw=hash
            //look in db for userhash
            //get salt + pwhash
            //hash(pwhash+salt) == dbpwhash 100 rounds
            //http://www.heise.de/security/artikel/Passwoerter-unknackbar-speichern-1253931.html
            //create sessionid timestamp+random
            
        
    //logout
            //delete session from db
    
    //create (user, email, pw)
        //pwhash = 256 x hash(pw)
        //salt = hash(timestamp + random);
        //final = 256 x hash(pwhash + salt);
    
    
    res.writeHead(200, {'Content-Type': 'text/plain'});
    res.end('user_handler\n');
}

//export functions
exports.game = game_handler; 
exports.lobby = lobby_handler;
exports.user = user_handler;