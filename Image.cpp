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

	Image::Image(const Image& rhs) {

		height = rhs.height;
		width = rhs.width;
		fileName = rhs.fileName;

		data = unique_ptr<unsigned char[]>(new char[rhs.width * rhs.height]);

		Image::iterator beg = this->begin(), end = this->end();
		Image::iterator inStart = rhs.begin(), inEnd = rhs.end();

		while (beg != inEnd) {
			*beg = *inStart;

			++beg;
			++inStart;
		}
	}

	Image::Image::operator=(const Image& rhs) {

		height = rhs.height;
		width = rhs.width;
		fileName = rhs.fileName;

		data = unique_ptr<unsigned char[]>(new char[rhs.width * rhs.height]);

		Image::iterator beg = this->begin(), end = this->end();
		Image::iterator inStart = rhs.begin(), inEnd = rhs.end();

		while (beg != inEnd) {
			*beg = *inStart;

			++beg;
			++inStart;
		}

		return *this;
	}

	Image::Image(Image&& rhs) {

		height = rhs.height;
		width = rhs.width;
		fileName = rhs.fileName;

		data = unique_ptr<unsigned char[]>(new char[rhs.width * rhs.height]);

		Image::iterator beg = this->begin(), end = this->end();
		Image::iterator inStart = rhs.begin(), inEnd = rhs.end();

		while (beg != inEnd) {
			*beg = *inStart;

			++beg;
			++inStart;
		}

		rhs.height = 0;
		rhs.width = 0;
		rhs.data = nullptr;
		rhs.fileName = "";
	}

	Image& Image::operator=(Image&& rhs) {

		height = rhs.height;
		width = rhs.width;
		fileName = rhs.fileName;

		data = unique_ptr<unsigned char[]>(new char[rhs.width * rhs.height]);

		Image::iterator beg = this->begin(), end = this->end();
		Image::iterator inStart = rhs.begin(), inEnd = rhs.end();

		while (beg != inEnd) {
			*beg = *inStart;

			++beg;
			++inStart;
		}

		rhs.height = 0;
		rhs.width = 0;
		rhs.data = nullptr;
		rhs.fileName = "";

		return *this;
	}

	Image::~Image() {

	}

	Image Image::operator+(const Image& rhs) const {
		if (height == rhs.height && width == rhs.width) {
			Image tmp(*this);

			Image::iterator beg = this->begin(), end = this->end();
			Image::iterator inStart = rhs.begin(), inEnd = rhs.end();

			while (beg != end) {
				int number = (int)(*beg) + (int)(*inStart);

				if (number > 255) {
					number = 255;
				}
				else if (number < 0) {
					number = 0;
				}

				*inStart = (unsigned char)(number);

				++beg;
				++inStart;
			}

			return tmp;
		}

		else {
			exit(1);
		}
	}

	Image Image::operator-(const Image& rhs) const {
		if (height == rhs.height && width == rhs.width) {
			Image tmp(*this);

			Image::iterator beg = this->begin(), end = this->end();
			Image::iterator inStart = rhs.begin(), inEnd = rhs.end();

			while (beg != end) {
				int number = (int)(*beg) - (int)(*inStart);

				if (number > 255) {
					number = 255;
				}
				else if (number < 0) {
					number = 0;
				}

				*inStart = (unsigned char)(number);

				++beg;
				++inStart;
			}

			return tmp;
		}

		else {
			exit(1);
		}
	}

	Image Image::operator!() const {

		Image tmp(*this);

		Image::iterator beg = begin(), end = end();
		Image::iterator inStart = tmp.begin();

		while (beg != end) {
			int number = 255 - (int)(*beg);

			if (number > 255) {
				number = 255;
			}
			else if (number < 0) {
				number = 0;
			}

			*inStart = (unsigned char)(number);

			++beg;
			++inStart;
		}

		return tmp;
	}

	Image Image::operator/(const Image& rhs) const {
		if (height == rhs.height && width == rhs.width) {
			Image tmp(rhs);

			Image::iterator beg = begin(), end = end();
			Image::iterator inStart = tmp.begin(), inEnd = tmp.end();

			while (beg != end) {
				int number = (int)(*beg);

				if (number > 255) {
					number = 255;
				}
				else if (number < 0) {
					number = 0;
				}

				*inStart = (unsigned char)(number);

				++beg;
				++inStart;
			}

			return tmp;
		}
	}
}