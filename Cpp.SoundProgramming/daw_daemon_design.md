
# DAW Daemon Design Document

Create a core library / daemon for embedded audio devices with DAW functionality

* Use IPC/Network protocol

## Supported UI principles

The base of a working project is a song.
An active working on "song type" has 2 working surfaces:

* 2 Main Views
	- Matrix View (MV) (similiar to Ableton, clip based)
	- Track View (TV) (classic track based)
		- With song phase feature
	
* The views presents a song subdivided into
	
	- Tracks
		- Midi
			- Input Device
			- Output Device
				- Instrument
				- Midi
			- Channel
			
		- Audio
			- Input Device
			- Output Device
			
		- Status
			- Muted
			- Piped
			- Focused/Active/Selected
			- Records
			
	
	- Live Tracks
		- Live handling of Midi/Audio for live performances
		- Pipe Input/Output through
	
	- Track Parts
		- Parts of the track
		- For each track only one track part at the same time possible
		
		- Midi
			- Free Pattern
			- Step Sequencer
	
		- Effects/Filter
			- Audio Effecs
			- Midi Effects
			
		- MV Settings
			- auto start
			- loop
			
		- Stats
			- Timings 
			- Running/Paused
			- Length
			- Records
			- Muted
			
	- Song phases 
		Presents switchable phases
		- e.g. intro, chorus, strophe, ...
		
	- Phase Glue
		Information to (automatic) switch between song phases
		- Automatic: After Time, X Loops etc
		- Event based on Midi/Audio/User input events, ...
		
		Also relevant to make switch between MV and TV possible
		
- Instruments
	- Additional for songs instruments can be defined
	- e.g. Synth (Midi In, Audio Out)
		
## Project Management
		
- Multiple Projects
	- Each project has multiple Songs
	- Songs:
		- MV/TV Working Song
			- Can be prerecorded
		- Fixed Audio File Song
		- "Live Song" for special live handling
			- Doing Mixing between songs with filter/effects ...
		- Referenced song of other project
	- Projects can be sorted in folder
		- Multiple folder mappings?
	
	
## Limitation
- Latency for to many stuff at the same time
