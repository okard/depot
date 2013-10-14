

#include <mpt/MPT.hpp>

#include <portaudio.h>

using namespace mpt;



void MPT::init()
{
	Pa_Initialize();
}

void MPT::shutdown()
{
	Pa_Terminate();
}
