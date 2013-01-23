/*
Copyright (c) 2013 okard

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in 
the Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies 
of the Software, and to permit persons to whom the Software is furnished to do 
so, subject to the following conditions: The above copyright notice and this 
permission notice shall be included in all copies or substantial portions of 
the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
SOFTWARE.
*/
#pragma once
#ifndef __SHELLNG_BUFFER__
#define __SHELLNG_BUFFER__

#include <shellng/Types.hpp>

namespace sng {

/**
* Memory Buffer Handling
*/
class Buffer
{
private:
	//pointer to memory
	ubyte8* buf_;
	
	//current content size
	std::size_t size_;
	
	//allocated memory size
	std::size_t allocMem_;
	
public:
	
	Buffer();
	Buffer(std::size_t size);
	Buffer(const Buffer& buf);
	//Buffer(const ubyte* const, std::size_t length);
	
	virtual ~Buffer();
	
	ubyte8 operator[](size_t offset);	

	void copyTo(Buffer& buf, std::size_t pos, std::size_t length);
	void resize(std::size_t size);	//control content size
	void alloc(std::size_t size);   //control allocated memory
	void shrink();					//shrink memory to content size
	
	void write(ubyte8* buf, std::size_t length);
	void write(std::size_t pos, ubyte8* buf, std::size_t length);
	
	std::size_t read(ubyte8* buf, std::size_t length);
	std::size_t read(std::size_t pos, ubyte8* buf, std::size_t length);
	
	inline ubyte8* const bufPtr() { return buf_; }
	inline ubyte8* const bufPtr(std::size_t offset) 
	{ 
		if(offset >= size_)
			return nullptr; //TODO exception?
		return &buf_[offset];
	}
	inline std::size_t size() { return size_; }
	inline std::size_t allocatedMemory() { return allocMem_; }
	
	//residualMemory() allocMem_-size_
	
};	

	

} //end namespace sng

#endif
