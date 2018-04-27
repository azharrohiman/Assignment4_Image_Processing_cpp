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

		data = unique_ptr<unsigned char[]>(new unsigned char[rhs.height * rhs.width]);

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

		data = unique_ptr<unsigned char[]>(new unsigned char[rhs.height * rhs.width]);

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

		data = unique_ptr<unsigned char[]>(new unsigned char[rhs.height * rhs.width]);

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

		data = unique_ptr<unsigned char[]>(new unsigned char[rhs.height * rhs.width]);

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

	Image Image::operator+(const Image& rhs) const
	{
		if(height == rhs.height && width == rhs.width)
		{
			Image tmp(*this);
			for(Image::iterator inStart = rhs.begin(), beg = tmp.begin(); inStart != rhs.end(); ++beg, ++inStart)
			{
				int number = (int)(*beg) + (int)(*inStart);
				if (number > 255) {
					number = 255;
				}
				else if (number < 0){
					number = 0;
				}
				*beg = (unsigned char)(number);
			}

			return tmp;
		}
		else {
			exit(1);
		}
	}

	Image Image::operator-(const Image& rhs) const
	{
		if(height == rhs.height && width == rhs.width)
		{
			Image tmp(*this);
			for(Image::iterator beg = tmp.begin(), inStart = rhs.begin(); inStart != rhs.end(); ++beg, ++inStart)
			{
				int number = (int)(*beg) - (int)(*inStart);
				if (number > 255) {
					number = 255;
				}
				else if (number < 0) {
					number = 0;
				}

				*beg = (unsigned char)(number);
			}

			return tmp;
		}
		else {
			exit(1);
		}
	}

	Image Image::operator!() const
	{
		Image tmp(*this);
		for(Image::iterator beg = begin(), inStart = tmp.begin(); beg != end(); ++beg, ++inStart)
		{
			int number = 255 - (int)(*beg);

			if (number > 255) {
				number = 255;
			}
			else if (number < 0) {
				number = 0;
			}

			*inStart = (unsigned char)(number);
		}

		return tmp;
	}

	Image Image::operator/(const Image& rhs) const
	{
		if(height == rhs.height && width == rhs.width)
		{
			Image tmp(rhs);
			for(Image::iterator inStart = tmp.begin(), beg = begin(); beg != end(); ++inStart, ++beg)
			{
				if((int)(*inStart) == 255)
				{
					if ((int)(*beg) > 255) {
						(int)(*beg) = 255;
					}
					else if ((int)(*beg) < 0) {
						(int)(*beg) = 0;
					}

					int number = ((int)(*beg));
					*inStart = (unsigned char)(number);
				}
			}

			return tmp;
		}

		else {
			exit(1);
		}
	}

	Image Image::operator*(const int threshold) const
	{
		Image tmp(*this);
		for(Image::iterator beg = begin(), inStart = tmp.begin(); beg != end(); ++beg, ++inStart)
		{
			if((int)(*inStart) <= threshold)
			{
				*inStart = (unsigned char)0;
			}
			else
			{
				*inStart = (unsigned char)255;
			}
		}

		return tmp;
	}


}