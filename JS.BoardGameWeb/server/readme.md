
Board Game Web Server
========================

node.js

(PostgresSQL + redis?)


Notices
------------------------
DB objects:
User (userid, username, pw_hash, salt, lastlogin, sessid)
Games (gameid, playera, playerb, creator, createddate, state, rules?)
  -> current state stored per gameid in nosql/redis?
  -> Moves (gameid, command, tokenid, field a, field b)

TokenList (tokenid, shortname, sitea, siteb, state, created, creator, default)