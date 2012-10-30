

#pragma once
#ifndef __LIBLMNG_LOGINMNG_HPP__
#define __LIBLMNG_LOGINMNG_HPP__

namespace lmng
{

/**
* Login Manager Interface Class
*/
class LoginMng
{
private:

public:

	//session?
		//startSession()
		//endSession()
	
	virtual void login(const char* user, const char* password);

	//logout
	//shutdown
	
};
	
}


#endif // __LIBLMNG_LOGINMNG_HPP__
