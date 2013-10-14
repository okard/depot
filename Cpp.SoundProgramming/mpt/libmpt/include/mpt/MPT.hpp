

#pragma once
#ifndef MPT_MPT_HPP
#define MPT_MPT_HPP

namespace mpt {
	
/**
* Music Production Toolkit 
* Core Management Class
*/
class MPT 
{
private:
	MPT() = delete;
	MPT(const MPT&) = delete;
	~MPT() = delete;

	//static bool initialized_;
	
	//ref tracking of audio/midi objects
public:

	//initialize toolkit
	static void init();
	
	//shutdown toolkit
	static void shutdown();
	
	//status
	
};
	
}


#endif // MPT_MPT_HPP
