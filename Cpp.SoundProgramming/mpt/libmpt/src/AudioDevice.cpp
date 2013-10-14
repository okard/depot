
#include <mpt/AudioDevice.hpp>

#include <iostream> //debug
#include <portaudio.h>

using namespace mpt;

/*
PaHostApiIndex 	Pa_GetHostApiCount (void)
PaHostApiIndex 	Pa_GetDefaultHostApi (void)
const PaHostApiInfo * 	Pa_GetHostApiInfo (PaHostApiIndex hostApi)
PaHostApiIndex 	Pa_HostApiTypeIdToHostApiIndex (PaHostApiTypeId type)
*/


//PaDeviceIndex 	Pa_GetDeviceCount (void)
//const PaDeviceInfo * 	Pa_GetDeviceInfo (PaDeviceIndex device)
//PaDeviceIndex 	Pa_GetDefaultInputDevice (void)
//PaDeviceIndex 	Pa_GetDefaultOutputDevice (void)

/*
PaDeviceInfo
 
int 	structVersion
const char * 	name
PaHostApiIndex 	hostApi
int 	maxInputChannels
int 	maxOutputChannels
PaTime 	defaultLowInputLatency
PaTime 	defaultLowOutputLatency
PaTime 	defaultHighInputLatency
PaTime 	defaultHighOutputLatency
double 	defaultSampleRate
*/

void AudioDevice::refresh()
{
	auto count = Pa_GetDeviceCount();
	
	for(decltype(count) i=0; i < count; i++)
	{
		auto info = Pa_GetDeviceInfo(i);
		
		std::cout << "Device [" << i << "]: " << info->name << std::endl;
		std::cout << '\t' << "Out: " << info->maxOutputChannels << " In: " << info->maxInputChannels << std::endl;
	}
}
	
