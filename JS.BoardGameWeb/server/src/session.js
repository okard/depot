/*
 BoardGame Web Server
 Session Handling
 Licensed under GPLv3
 Author: okard
*/

var crypto = require('crypto');
var util = require('./util.js');


var sessions = {};

var SESSIONID = 'sessionid';
var TIMEOUT = 3*60*1000;


//TODO Associate IP with Session, (Cookie Stealing) Way to disable (AOL Problems?)
//TODO Session via url parameter? not better?

/**
* Starts session
*/
exports.start = function(req, res)
{
    var sess = getSession(req);
    
    if(sess)
    {
        console.log("session: " + JSON.stringify(sess));
        return;
    }
    
    //else starts session
    var sid = createSID(req.headers.host);
    
    //set session object
    sessions[sid] = {};
    
    var value = SESSIONID + "=" + sid + ";Version=1";
    //res.setHeader('Set-Cookie2', value);
    res.setHeader('Set-Cookie', value);
    //"Secure" (optional)
    //"Version=1;Secure"
    //"Max-Age" "=" value
}

/**
* Get Session Object
*/
function getSession(req)
{
    var c = util.cookies(req);
    
    if(c[SESSIONID])
    {
        return sessions[c[SESSIONID]];
    }
    else
       return null;
}

/**
* Create a session id
*/
function createSID(host)
{
    var shasum = crypto.createHash('sha256');
    var time = new Date().getTime();
    shasum.update(host + time);
    return shasum.digest('hex');
}

/**
* sets value
*/
exports.set = function(req, key, value)
{
    var sess = getSession(req);
    
    if(sess)
    {
        sess[key] = value;
    }
}

/**
* get value
*/
exports.get = function(req, key)
{
    var sess = getSession(req);
    
    if(sess)
    {
        return sess[key];
    }
    else
        return null;
}

/**
* End Session
*/
exports.end = function(req, res)
{
    //delete cookie
    //set expire data
    var value = SESSIONID + "=;Version=1;Max-Age=1";
    res.setHeader('Set-Cookie', value);
}



