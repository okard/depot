
Board Game Web Server
========================

node.js

(PostgresSQL + redis?)

npm install redis
npm install pg


Notices
------------------------
DB objects:
User (userid, username, usernamehash, pw_hash, salt, email, lastlogin, sessid)
Games (gameid, playera, playerb, creator, createddate, state, rules?)
  -> current state stored per gameid in nosql/redis?
  -> Moves (gameid, command, tokenid, field a, field b)

TokenList (tokenid, shortname, sitea, siteb, state, created, creator, default)