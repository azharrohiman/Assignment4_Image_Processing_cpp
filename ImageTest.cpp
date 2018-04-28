#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Image.h"

using namespace RHMMUH005;
using namespace std;

TEST_CASE("Copy Constructor/Assignment", "[copy operators]") {

	SECTION("Default Constructor") {
		Image image;
		REQUIRE(image.width == 0);
		REQUIRE(image.height == 0);
		REQUIRE(image.data == nullptr);
	}

	unique_ptr<unsigned char[]> data = unique_ptr<unsigned char[]>{new unsigned char[4]{255, 0, 255, 0}};

	Image image1(move(data), 2, 2);

	SECTION("Data Construction") {
		REQUIRE(image1.width == 2);
		REQUIRE(image1.height == 2);

		REQUIRE(image1.data[0] == 255);
		REQUIRE(image1.data[1] == 0);
		REQUIRE(image1.data[2] == 255);
		REQUIRE(image1.data[3] == 0);
	}

	SECTION("Copy Constructor") {

		Image image2(image1);

		REQUIRE(image1.width == 2);
		REQUIRE(image1.height == 2);
		REQUIRE(image2.width == 2);
		REQUIRE(image2.height == 2);

		REQUIRE(image1.data[0] == 255);
		REQUIRE(image1.data[1] == 0);
		REQUIRE(image1.data[2] == 255);
		REQUIRE(image1.data[3] == 0);

		REQUIRE(image2.data[0] == 255);
		REQUIRE(image2.data[1] == 0);
		REQUIRE(image2.data[2] == 255);
		REQUIRE(image2.data[3] == 0);
	}

	SECTION("Copy Assignment") {

		Image image2;
		image2 = image1;

		REQUIRE(image1.width == 2);
		REQUIRE(image1.height == 2);
		REQUIRE(image2.width == 2);
		REQUIRE(image2.height == 2);

		REQUIRE(image1.data[0] == 255);
		REQUIRE(image1.data[1] == 0);
		REQUIRE(image1.data[2] == 255);
		REQUIRE(image1.data[3] == 0);

		REQUIRE(image2.data[0] == 255);
		REQUIRE(image2.data[1] == 0);
		REQUIRE(image2.data[2] == 255);
		REQUIRE(image2.data[3] == 0);
	}
}


TEST_CASE("Move Constructor/Assignment", "[move operators]") {

	unique_ptr<unsigned char[]> data = unique_ptr<unsigned char[]>{new unsigned char[4]{255, 0, 255, 0}};

	Image image1(move(data), 2, 2);

	REQUIRE(image1.width == 2);
	REQUIRE(image1.height == 2);

	SECTION("Move Constructor") {

		Image image2(move(image1));

		REQUIRE(image1.width == 0);
		REQUIRE(image1.height == 0);
		REQUIRE(image2.width == 2);
		REQUIRE(image2.height == 2);

		REQUIRE(image1.data == nullptr);

		REQUIRE(image2.data[0] == 255);
		REQUIRE(image2.data[1] == 0);
		REQUIRE(image2.data[2] == 255);
		REQUIRE(image2.data[3] == 0);
	}

	SECTION("Move Assignment") {

		Image image2;
		image2 = move(image1);

		REQUIRE(image1.width == 0);
		REQUIRE(image1.height == 0);
		REQUIRE(image2.width == 2);
		REQUIRE(image2.height == 2);

		REQUIRE(image1.data == nullptr);

		REQUIRE(image2.data[0] == 255);
		REQUIRE(image2.data[1] == 0);
		REQUIRE(image2.data[2] == 255);
		REQUIRE(image2.data[3] == 0);
	}
}

TEST_CASE("Addition", "[Adding images]") {

	unique_ptr<unsigned char[]> data = unique_ptr<unsigned char[]>{new unsigned char[4]{255, 0, 255, 0}};

	Image image1(move(data), 2, 2);

	unique_ptr<unsigned char[]> data2 = unique_ptr<unsigned char[]>{new unsigned char[4]{0, 255, 255, 0}};

	Image image2(move(data2), 2, 2);

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

	unique_ptr<unsigned char[]> data = unique_ptr<unsigned char[]>{new unsigned char[4]{255, 0, 255, 0}};

	Image image1(move(data), 2, 2);

	unique_ptr<unsigned char[]> data2 = unique_ptr<unsigned char[]>{new unsigned char[4]{0, 255, 255, 0}};

	Image image2(move(data2), 2, 2);

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

	unique_ptr<unsigned char[]> data = unique_ptr<unsigned char[]>{new unsigned char[4]{255, 0, 255, 0}};

	Image image1(move(data), 2, 2);

	unique_ptr<unsigned char[]> data2 = unique_ptr<unsigned char[]>{new unsigned char[4]{0, 255, 255, 0}};

	Image image2(move(data2), 2, 2);

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

	unique_ptr<unsigned char[]> data = unique_ptr<unsigned char[]>{new unsigned char[4]{255, 0, 255, 0}};

	Image image1(move(data), 2, 2);

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

	unique_ptr<unsigned char[]> data = unique_ptr<unsigned char[]>{new unsigned char[4]{255, 0, 255, 0}};

	Image image1(move(data), 2, 2);

	unique_ptr<unsigned char[]> data2 = unique_ptr<unsigned char[]>{new unsigned char[4]{0, 255, 255, 0}};

	Image image2(move(data2), 2, 2);

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
