#define CATCH_CONFIG_MAIN

#include "Image.h"
#include "catch.hpp"

using namespace RHMMUH005;

TEST_CASE("Copy Constructor/Assignment", "[copy operators]") {

	unsigned char* arr = new unsigned char[4];

	arr[0] = (unsigned char) 255;
	arr[1] = (unsigned char) 0;
	arr[2] = (unsigned char) 255;
	arr[3] = (unsigned char) 0;

	Image image1(&arr, 2, 2);

	REQUIRE(image1.width == 2);
	REQUIRE(image1.height == 2);

	SECTION("Copy Constructor") {

		Image image2(image1);

		REQUIRE(image1.width == 2);
		REQUIRE(image1.height == 2);
		REQUIRE(image2.width == 2);
		REQUIRE(image2.height == 2);
	}

	SECTION("Copy Assignment") {

		Image image2;
		image2 = image1;

		REQUIRE(image1.width == 2);
		REQUIRE(image1.height == 2);
		REQUIRE(image2.width == 2);
		REQUIRE(image2.height == 2);
	}
}

TEST_CASE("Move Constructor/Assignment", "[move operators]") {

	unsigned char* arr = new unsigned char[4];

	arr[0] = (unsigned char) 255;
	arr[1] = (unsigned char) 0;
	arr[2] = (unsigned char) 255;
	arr[3] = (unsigned char) 0;

	Image image1(&arr, 2, 2);

	REQUIRE(image1.width == 2);
	REQUIRE(image1.height == 2);

	SECTION("Move Constructor") {

		Image image2(std::move(image1));

		REQUIRE(image1.width == 0);
		REQUIRE(image1.height == 0);
		REQUIRE(image2.width == 2);
		REQUIRE(image2.height == 2);
	}

	SECTION("Move Assignment") {

		Image image2;
		image2 = std::move(image1);

		REQUIRE(image1.width == 0);
		REQUIRE(image1.height == 0);
		REQUIRE(image2.width == 2);
		REQUIRE(image2.height == 2);
	}
}

TEST_CASE("Addition", "[Adding images]") {

	unsigned char* arr = new unsigned char[4];

	arr[0] = (unsigned char) 255;
	arr[1] = (unsigned char) 0;
	arr[2] = (unsigned char) 255;
	arr[3] = (unsigned char) 0;

	unsigned char* arr2 = new unsigned char[4];

	arr2[0] = (unsigned char) 0;
	arr2[1] = (unsigned char) 255;
	arr2[2] = (unsigned char) 255;
	arr2[3] = (unsigned char) 0;

	Image image1(&arr, 2, 2);
	Image image2(&arr2, 2, 2);

	SECTION("Addition Test") {
		int  imageArray[] = {255, 255, 255, 0};

		Image addition = image1 + image2;

		Image::iterator beg = addition.begin();

		int i = 0;

		while (beg != addition.end()) {

			REQUIRE(imageArray[i] == (int)(*beg));

			++beg;
			i++;
		}
	}
}

TEST_CASE("Subtraction", "[Subtracting images]") {

	unsigned char* arr = new unsigned char[4];

	arr[0] = (unsigned char) 255;
	arr[1] = (unsigned char) 0;
	arr[2] = (unsigned char) 255;
	arr[3] = (unsigned char) 0;

	unsigned char* arr2 = new unsigned char[4];

	arr2[0] = (unsigned char) 0;
	arr2[1] = (unsigned char) 255;
	arr2[2] = (unsigned char) 255;
	arr2[3] = (unsigned char) 0;

	Image image1(&arr, 2, 2);
	Image image2(&arr2, 2, 2);

	SECTION("Subtraction Test") {
		int imageArray[] = {255, 0, 0, 0};

		Image subtraction = image1 - image2;

		Image::iterator beg = subtraction.begin();

		int i = 0;

		while (beg != subtraction.end()) {

			REQUIRE(imageArray[i] == (int)(*beg));

			++beg;
			i++;
		}
	}
}

TEST_CASE("Inverting", "[Invert Image]") {

	unsigned char* arr = new unsigned char[4];

	arr[0] = (unsigned char) 255;
	arr[1] = (unsigned char) 0;
	arr[2] = (unsigned char) 255;
	arr[3] = (unsigned char) 0;

	unsigned char* arr2 = new unsigned char[4];

	arr2[0] = (unsigned char) 0;
	arr2[1] = (unsigned char) 255;
	arr2[2] = (unsigned char) 255;
	arr2[3] = (unsigned char) 0;

	Image image1(&arr, 2, 2);
	Image image2(&arr2, 2, 2);

	SECTION("Invert Test") {
		int imageArray[] = {0, 255, 0, 255};

		Image invrt = !image1;

		Image::iterator beg = invrt.begin();

		int i = 0;

		while (beg != invrt.end()) {
			REQUIRE(imageArray[i] == (int)(*beg));

			++beg;
			i++;

		}
	}
}

TEST_CASE("Threshold", "[Threshold]") {

	unsigned char* arr = new unsigned char[4];

	arr[0] = (unsigned char) 255;
	arr[1] = (unsigned char) 0;
	arr[2] = (unsigned char) 255;
	arr[3] = (unsigned char) 0;

	Image image1(&arr, 2, 2);

	SECTION("Threshold Test") {
		int imageArray[] = {255, 0, 255, 0};

		Image threshold = image1 * 200;

		Image::iterator beg = threshold.begin();

		int i = 0;

		while (beg != threshold.end()) {
			REQUIRE(imageArray[i] == (int)(*beg));

			++beg;
			i++;
		}

	}
}

TEST_CASE("Masking", "[Masking Test]") {

	unsigned char* arr = new unsigned char[4];

	arr[0] = (unsigned char) 255;
	arr[1] = (unsigned char) 0;
	arr[2] = (unsigned char) 255;
	arr[3] = (unsigned char) 0;

	unsigned char* arr2 = new unsigned char[4];

	arr2[0] = (unsigned char) 0;
	arr2[1] = (unsigned char) 255;
	arr2[2] = (unsigned char) 255;
	arr2[3] = (unsigned char) 0;

	Image image1(&arr, 2, 2);
	Image image2(&arr2, 2, 2);

	SECTION("Masking Test") {
		int imageArray[] = {0, 0, 255, 0};

		Image mask = image1/image2;

		Image::iterator beg = mask.begin();

		int i = 0;

		while (beg != mask.end()) {
			REQUIRE(imageArray[i] == (int)(*beg));

			++beg;
			i++;
		}
	}
}
