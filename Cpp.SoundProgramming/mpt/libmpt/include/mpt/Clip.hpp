
#pragma once
#ifndef MPT_CLIP_HPP
#define MPT_CLIP_HPP

namespace mpt {
	

enum class ClipStatus
{
	Running,
	Paused,
	Stopped
}	


/**
* Represents a chunk of Audio/Midi Data
*/
class Clip
{
private:
	bool loop_;
	long position_;
	
public:

	//loop
	//status: running, paused, stopped
	//starttime?
	//endtime?
	
};


//MidiClip
//AudioClip

} //end namespace mpt

#endif // MPT_CLIP_HPP
