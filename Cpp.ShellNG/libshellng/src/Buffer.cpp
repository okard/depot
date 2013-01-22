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

#include <shellng/Buffer.hpp>
#include <shellng/Exception.hpp>

#include <cstdlib>
#include <cstring>

using namespace sng;


Buffer::Buffer()
	: buf_(nullptr), size_(0), allocMem_(0)
{
}

Buffer::Buffer(std::size_t size)
{
	this->resize(size);
}

Buffer::Buffer(const Buffer& buf)
{
	//copy
	//buf.copyTo(*this, 0, buf.size_);
	
}

Buffer::~Buffer()
{
	size_ = 0;
	allocMem_ = 0;
	
	if(buf_ != nullptr)
		free(buf_);
		

}

ubyte8 Buffer::operator[](size_t offset)
{
	if(offset < 0 && offset > (size_ -1))
		throw Exception("out of index");
	
	//return byte at this position
	return buf_[offset];
}


void Buffer::copyTo(Buffer& buf, std::size_t pos, std::size_t length)
{
	write(pos, buf.buf_, length);
	//size_ 
}

void Buffer::resize(std::size_t size)
{
	//no buffer allocated start new
	if(buf_ == nullptr)
	{
		buf_ = reinterpret_cast<ubyte8*>(malloc(size));
		
		//check
		if(buf_ == NULL)
		{
			buf_ = nullptr;
			throw Exception("failed to alloc memory");
		}
		
		memset (buf_, 0, size);
		allocMem_ = size;
		size_ = 0;
		
		return;
	}
	
	if(size <= allocMem_)
	{
		size_ = size;
		return;
	}

	//reallocated memory
	void* tmp = realloc(buf_, size);
	
	if(tmp == NULL)
		throw Exception("failed to realloc memory");
	
	//memset new allocated memory
	
	buf_ = reinterpret_cast<ubyte8*>(tmp);
	size_ = 0;
	allocMem_ = size;
}


void Buffer::shrink()
{
	//TODO set allocMem size to size_
	//realloc
	
}


void Buffer::write(ubyte8* buf, std::size_t length)
{
	write(0, buf, length);
}

void Buffer::write(std::size_t pos, ubyte8* buf, std::size_t length)
{
	//check size
	//realloc
	//copy
	
	//allocate more memory if required
	if(pos+length > allocMem_)
		resize(pos+length);
		
	memcpy (&buf_[pos], buf, length);
	
	//set a new size if buffer content is now bigger
	if(pos + length > size_)
		size_ = pos + length;
}

std::size_t Buffer::read(ubyte8* buf, std::size_t length)
{
	return read(0, buf, length);
}

std::size_t Buffer::read(std::size_t pos, ubyte8* buf, std::size_t length)
{
	//check own size
	
	//not enough data to read so shrink size
	if(pos+length > size_)
		length = size_-pos;
		
	memcpy(buf, &buf_[pos], length);
	
	return 0;
}
	
