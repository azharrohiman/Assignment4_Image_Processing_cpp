#ifndef IMAGE_H
#define IMAGE_H

#include <memory>
#include <string>

namespace RHMMUH005 {
	
	class Image {
		private:
			int height, width;
			std::unique_ptr<unsigned char[]> data;
			std::string fileName;

		public:
			Image();
			//
			Image(const Image& rhs);
			Image& operator=(const Image & rhs);
			Image(Image&& other);
			Image& operator=(Image&& rhs);

			~Image();

			Image operator+(const Image& rhs) const;

			Image operator-(const Image& rhs) const;

			Image operator!() const;

			Image operator/(const Image& rhs) const;

			Image operator*(const int threshold) const;

			void loadImage(std::string fileName);
			void saveImage(std::string fileName);
	};
}