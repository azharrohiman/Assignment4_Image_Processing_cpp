#include <string>
#include <iostream>

#include "Image.h"

int main(int argc, char* argv[]) {

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
			cout << "Inverting image " << image1Name << " to " << output << endl;
			imageOutputObj = !image1Obj;
		}
	}

	else if (argc == 5) {
		if (operation == "-a" || operation == "-s" || operation == "-l") {

			if (operation == "-a") {
				cout << "Adding images " << image1Name << " and " << argv[3] << " to produce " << output << endl;
				image2Obj.loadImage(argv[3]);
				imageOutputObj = image1Obj + image2Obj;
			}

			else if (operation == "-s") {
				cout << "Subtracting " << argv[3] << " from " << image1Name << " to produce " << output << endl;
				image2Obj.loadImage(argv[3]);
				imageOutputObj = image1Obj - image2Obj;
			}

			else if (operation == "-l") {
				cout << "Masking image " << image1Name << " and " << argv[3] << " to " << output << endl;
				image2Obj.loadImage(argv[3]);
				imageOutputObj = image1Obj/image2Obj;
			}
		}

		else if (operation == "-t") {
			cout << "Threshold operation on image " << image1Name << " to " << output << endl;
			int threshold = stoi(argv[3]);
			imageOutputObj = image1Obj * threshold;
		}
	}

	imageOutputObj.saveImage(output);

	return 0;
}
