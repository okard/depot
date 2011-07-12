/*
 BoardGame Web Server
 User Resource
 Licensed under GPLv3
 Author: okard
*/

var util = require('./util.js');
var session = require('./session.js');


/**
* Http '/user' Handler
*/
exports.handler = function(req, url, res)
{
    session.start(req, res);
    
    //Check Parameter
    if(url.pathname.length >= 2)
    switch(url.pathname[1])
    {
        case 'login':
            //check if already logged in?
            //user/password
            session.set(req, 'userid', Math.random());
            console.log("do login");
            util.sendJson(res, {action: 'login', status: 'ok'});
            return;
            break;
            
        case 'logout':
            session.end(req, res);
            console.log("do logout");
            util.sendJson(res, {action: 'logout', status: 'ok'});
            return;
            break;
       
        case 'status':
            var userid = session.get(req, 'userid');
            if(userid)
            {
                util.sendJson(res, {userid: userid});
            }
            else
                util.sendError(res, 40, 'not logged in');
            return;
            break;
    }
   
    //logout
            //delete session from db
    
    //create (user, email, pw)
        //pwhash = 256 x hash(pw)
        //salt = hash(timestamp + random);
        //final = 256 x hash(pwhash + salt);

    util.send404(req, res);
}


/**
* Login Function
*/
function login()
{
    //login (session cookie) /game/login?user=abc&pw=hash
    //look in db for userhash
    //get salt + pwhash
            //hash(pwhash+salt) == dbpwhash 100 rounds
            //http://www.heise.de/security/artikel/Passwoerter-unknackbar-speichern-1253931.html
            //create sessionid timestamp+random
    
}