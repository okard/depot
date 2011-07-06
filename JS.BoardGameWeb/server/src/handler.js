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
    console.log(session.get(req, 'userid') ? "authorized" : "not authorized");
     
    //extract session id
    //validate session
    
    //actions
    //-create
    //-spectate
    //-move
    //-pick
    //-
    
    var header = {
        'Content-Type': 'application/json'
    }
    
    res.writeHead(200, header);
    res.end(JSON.stringify("game_handler"));    
}

/**
* Lobby Handler
* Handle Lobby Functions, Messaging ,etc
*/
function lobby_handler(req, url, res)
{
   
    //validate session
    
    res.writeHead(200, {'Content-Type': 'text/plain'});
    res.end('lobby_handler\n');
}

/**
* User Handler
* Handle Logins, Logouts, etc
*/
function user_handler(req, url, res)
{
    session.start(req, res);
    
    if(url.pathname.length >= 2)
    switch(url.pathname[1])
    {
        case 'login':
            //check if already logged in?
            session.set(req, 'userid', Math.random());
            console.log("do login");
            util.sendJson(res, {'action' : 'login', 'status' : 'ok'});
            return;
            break;
            
        case 'logout':
            session.end(req, res);
            console.log("do logout");
            util.sendJson(res, {'action' : 'logout', 'status' : 'ok'});
            return;
            break;
       
        case 'status':
            var userid = session.get(req, 'userid');
            if(userid)
            {
                util.sendJson(res, {'userid' : userid});
            }
            else
                util.sendJson(res, {'error' : 'not logged in'});
            return;
            break;
    }
   
    
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

    util.send404(req, res);
}

//export functions
exports.game = game_handler; 
exports.lobby = lobby_handler;
exports.user = user_handler;