#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#incldue <sstream>

#include "Image.h"

using namespace std;

namespace RHMMUH005 
{
	Image::Image() {

		height = 0;
		width = 0;
		data = nullptr;
		fileName = "";
	}

	//

	Image::Image(const Image& rhs)
	{
		width = rhs.width;
		height = rhs.height;
		imgName = rhs.imgName;

		data = unique_ptr<u_char[]>(new u_char[rhs.height * rhs.width]);

		for(Image::iterator beg = begin(), inStart = rhs.begin(); inStart != rhs.end(); ++beg, ++inStart)
		{
			*beg = *inStart;
		}
	}

	Image& Image::operator=(const Image& rhs)
	{
		width = rhs.width;
		height = rhs.height;
		imgName = rhs.imgName;

		data = unique_ptr<u_char[]>(new u_char[rhs.height * rhs.width]);

		for(Image::iterator beg = begin() , inStart = rhs.begin(); inStart != rhs.end(); ++beg, ++inStart)
		{
			*beg = *inStart;
		}

		return *this;
	}

	Image::Image(Image&& rhs)
	{
		width = rhs.width;
		height = rhs.height;
		imgName = rhs.imgName;

		data = unique_ptr<u_char[]>(new u_char[rhs.height * rhs.width]);

		for(Image::iterator beg = begin() , inStart = rhs.begin(); inStart != rhs.end(); ++beg, ++inStart)
		{
			*beg = *inStart;
		}

		rhs.width = 0;
		rhs.height = 0;
		rhs.data = nullptr;
		rhs.imgName = "";
	}

	Image& Image::operator=(Image&& rhs)
	{
		width = rhs.width;
		height = rhs.height;
		imgName = rhs.imgName;

		data = unique_ptr<u_char[]>(new u_char[rhs.height * rhs.width]);

		for(Image::iterator inStart = rhs.begin(), beg = begin(); inStart != rhs.end(); ++inStart, ++beg)
		{
			*beg = *inStart;
		}

		rhs.width = 0;
		rhs.height = 0;
		rhs.data = nullptr;
		rhs.imgName = "";

		return *this;
	}

	Image::~Image() {

	}


}