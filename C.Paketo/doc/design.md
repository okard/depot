Design of Paketo Package Management
========================================

Objects:
----------------------------------------

* Repository Roots (e.g. GIT-Repository)
    - Contains Package Defintions
    - Source of Repositories
* Package Defintion
    - Elements of Repository Root
    - Base of Source Packages
    - Contains Information howto create package
    - Can create multiple packages from one Package Definition (splitted packages)
* Repositories
    - Contains Packages
    - Name (e.g. core)
    - Arch (e.g. any, x86_64, i686, arm)
    - DB (KC/JSON/COMPRESSED JSON/...) (local vs remote)
    - Package-Types (bin, src, src-full)
* Packages
    - Name
    - Version
    - etc

Tools Usage:
----------------------------------------

* repoman 
    - Repository Root -> Repositories
    - Create Packages
    - Binary Packages builded from Package Definitions
    - Source Packages are archived Package Definitions from Repository Root
    - Create Repository DB
* paketo
    - Sync Repositories DB (rsync?, file download)
    - Build Source Packages to Binary Packages
    - Handle Binary Packages (Install, Remove, Update)
    
    

Build Process:
----------------------------------------

* Support Package Definition Scripts for Bash (Lua, Python, ???)
* Use IPC to handle these subprocesses
* Call Script Interpreter and injects/load Package Library

