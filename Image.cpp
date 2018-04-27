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

	void Image::saveImage(string saveFile) {
		ofstream file(saveFile, ios::out | ios::binary);

		file << "P5" << endl;
		file << "#" << saveFile << endl;
		file << width << " " << height << endl;
		file << "255" << endl;

		file.write((char*).data.get(), width*height);
		file.close();
	}

	void Image::loadImage(string loadFile) {
		ifstream file(loadFile, ios::in | ios::binary);
		fileName = loadFile;

		string line;

		while (!file.eof()) {
			getline(file, line);

			if (line[0] == '#' || line == "P5") {
				continue;
			}

			else if (line == "255") {
				break;
			}

			else {
				stringstream ss(line);
				string number;

				getline(ss, number, ' ');
				width = stoi(number);

				getline(ss, number, ' ');
				height = stoi(number);
			}
		}

		unsigned char *imgbytes = new unsigned char[width*height];
		file.read((char*) imgbytes, width*height);
		file.close();

		data = unique_ptr<unsigned char[]>(imgbytes);
		
		/*
		ifstream ifsFileIn(fName, ios::in|ios::binary);
		imgName = fName;
		string ln;
		getline(ifsFileIn, ln);
		hdr = hdr + ln + "\n";
		getline(ifsFileIn, ln);
		while(ln[0] == '#')
		{
		hdr = hdr + ln + "\n";   
		getline(ifsFileIn, ln);
		}
		istringstream w_and_h(ln);
		w_and_h >> width >> height;
		int numbers;
		ifsFileIn >> numbers >> ws;
		int dmn = height * width;
		data = unique_ptr<u_char[]>(new u_char[dmn]);
		ifsFileIn.read((char*)data.get(), dmn);
		ifsFileIn.close();
		*/
	}

	const Image::iterator& Image::iterator::operator++()
	{
		ptr ++;
		return *this;
	}

	const Image::iterator& Image::iterator::operator--()
	{
		ptr --;
		return *this;
	}

	unsigned char& Image::iterator::operator*() {
		return *ptr;
	}

	Image::iterator& Image::iterator::operator=(const Image::iterator& rhs)
	{
		ptr = rhs.ptr;
		return *this;
	}

	Image::iterator& Image::iterator::operator=(Image::iterator&& rhs)
	{
		ptr = rhs.ptr;
		rhs.ptr = nullptr;    
		return *this;
	}

	bool Image::iterator::operator==(const Image::iterator& rhs) {
		return (ptr == rhs.ptr);
	}

	bool Image::iterator::operator!=(const Image::iterator& rhs) {
		return (ptr != rhs.ptr);
	}

	Image::iterator Image::begin(void) const {
		return iterator(data.get());
	}

	Image::iterator Image::end() const {
		return iterator(&data[width*height]);
	}

	ofstream& operator<<(ofstream& os, const Image& image) {
		os << "P5" << "#" << image.width << " " << image.height << '\n' << 255 << endl;
		os.write((char*)image.data.get(), image.width*image.height);

		return os;
	}

	istream& operator>>(istream& is, Image& image) {
		
	}
}