

#include <mpt/MPT.hpp>
#include <mpt/AudioDevice.hpp>

using namespace mpt;

int main(int argc, char *argv[])
{
	
	MPT::init();
	
	AudioDevice::refresh();
	
	//console control
	
	//main loop
		//update(time)
	
	
	MPT::shutdown();
}
