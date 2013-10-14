

#pragma once
#ifndef MPT_AUDIODEVICE_HPP
#define MPT_AUDIODEVICE_HPP

#include <mpt/AudioInputStream.hpp>
#include <mpt/AudioOutputStream.hpp>
#include <mpt/AudioDuplexStream.hpp>

//port audio forward declaration
struct PaDeviceInfo;

namespace mpt {
	
/**
* Audio Device
*/
class AudioDevice
{
	
private:
	//PaDeviceId //multiple?
	
	int deviceId_;
	const PaDeviceInfo* deviceInfp_;
	
	
	AudioDevice(int id);
	
	//central streams?
	
	//static count?
public:

	//has input channels
	//has output channels
	
	//sample rate?
	//latency?
	
	//outputstreams
		//count
		//create
	//inputstreams
		//count
		//create
		
	//createDefaultOutputStream?
	
	//static AudioDevice[] get();
	
	//static int Count();
	
	static void refresh();
	
};


} //end namespace mpt

#endif //MPT_AUDIODEVICE_HPP
