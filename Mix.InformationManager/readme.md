
# Information Manager

Idea / Concept:

Tool for managing different Information in closed groups.

Possible to run a dedicated server or personal nodes
	- Business Enviroment
	- Support permission system

P2P Concept similiar to syncthing
Also combine with decentral XMPP/Jabber approch to connect other networks?
Can be used for team information management 


## Notices

Using Multicast? for local networks? Only to find Nodes?
	-> Connect to multicast, send request, no answer -> create server
	
Node ( One Node Represents User?/Group? , One Node can handle multiple users?)
	* Name
	* ID
		- Group
		- User
	* Parent Object (Repository)
	* 

Connect to other Nodes (P2P Network, Client-Server Network)
Subscribe to Repos?
	- owned 
	- via group
	
	
## Information / Objects

Organize in a style similar to git?

* Core Object
	- Tag (Search, Organisation in Trees?, Application Tag )
	
	- Permissions: User/Groups Right Management
		* Read
		* Write
		* Change Permission
		* Accept new Groups/User
		* Public Viewable?

* Support Trees to organize Objects

* Event / Interupt Support
	- Non persistent object

* Async merging/syncing when working on same stuff

* Wiki Pages
	- History?
	- Title
	- Attachments
	- References
* Link Collections
* Files (Binary Object)
	- (Sync folder? or only VFS?)
* Tasks / Log 
	 Date/User/Desc
* Groups 
	- User/Groups

* With extended frontends also simple txt (md,json,xml) files can be a complex application
	- e.g. scrum task board


## Workflows

Local Node: 

	1. Start Node
	2. Connect to other nodes (broadcast, etc?)
		2.1 Other Nodes must accept the connection 
		2.2 Check Groups, permissions on other nodes
	3. Create new Repository or Subscribe to one
		3.1 Check other nodes when new group subscriptions happened
		3.2 Save Permission <-> Repository ID
	4. Syncing?/Initialization?
	5. Working

Central Node (Server):
	1. Connect to frontend (user of Node Group)
	2. Authorize to Node
	3. Look for personal Settings 

## Architecture

* core library
	- basic data structure
		- object definitions
	- protocol implementation?
		- MsgPack based?
	- storage
		- DB (NoSQL, Relative)
		- DVCS (git? -> libgit2)
		- Filesystem
		- Memory

* core daemon 
	- service 
	- running protocol 
	- 
	
* api REST (HTTP)
	- api to use daemon via HTTP 
	- creating web gui
	
* frontend web
	- HTML5/JS 
	
* other frontends possible

## Protocol?
	
* Get Permissions
* Get Repository
* Get Repository Data
	- Object Syncing
* Get Repository List
* Get Node List
* Send Node Connect Request (Stun, upnp, etc)
