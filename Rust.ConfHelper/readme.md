# ConfigHelper




Tool for synchronizing 2 directories for example for storing configs in a git repository


Directions:
	
	Source - Target
	Target - Source
	
	
	Source -> Repo ?
	Target -> $HOME ?
	
Determine one automatically


Configs

	~/.config_confh
	{WD}/.config_confh
	

Ideas:
	
In repo:

	$ confh info .bashrc
	
In $HOME:
	
	$ confh info .bashrc
	
Commands:
	
	$ confh -n new
	$ confh -d diff
	$ confh -t 
	$ confh -s 
	$ confh -i info
	
	$ confh --init??
	
Config:
	
```toml

target="~/"
source="~/20.Dev/10.Projects/zz.Configs/"

# multiple dirs?

```
