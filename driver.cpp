#include <string>
#include <iostream>

#include "Image.h"

int main(int argc, char* argv[]) {
	
	//using namespace RHMMUH005;
	using namespace std;

	string operation = argv[1];
	string image1Name = argv[2];

	RHMMUH005::Image image1Obj;
	image1Obj.loadImage(image1Name);

	RHMMUH005::Image image2Obj;

	string output = argv[argc - 1];
	RHMMUH005::Image imageOutputObj;

	if (argc == 4) {
		if (operation == "-i") {
			imageOutputObj = !image1Obj;
		}
	}

	else if (argc == 5) {
		if (operation == "-a" || operation == "-s" || operation == "-l") {

			if (operation == "-a") {
				image2Obj.loadImage(argv[3]);
				imageOutputObj = image1Obj + image2Obj;
			}

			else if (operation == "-s") {
				image2Obj.loadImage(argv[3]);
				imageOutputObj = image1Obj - image2Obj;
			}

			else if (operation == "-l") {
				image2Obj.loadImage(argv[3]);
				imageOutputObj = image1Obj/image2Obj;
			}
		}

		else if (operation == "-t") {
			int threshold = stoi(argv[3]);
			imageOutputObj = image1Obj * threshold;
		}
	}

	imageOutputObj.saveImage(output);

	return 0;
}
