#include <iostream>
#include <fstream>
using namespace std;

struct Image {
	int mx;
	int my;
	int* points;
};

void createImage(Image* img, int tmx, int tmy) {
	img->mx = tmx;
	img->my = tmy;
	img->points = new int[tmx * tmy]{ 1 };
}

void showImage(Image* img) {
	for (int y = 0; y < img->my; y++) {
		for (int x = 0; x < img->mx; x++) {
			cout << img->points[y * img->mx + x] << " ";
		}
		cout << endl;
	}
}

void setPointImage(Image* img, int x, int y, int color) {
	img->points[y * img->mx + x] = color;
}

int getPointImage(Image* img, int x, int y) {
	return img->points[y * img->mx + x];
}

void saveToPnmFile(Image* img, string fileName) {
	fstream out;
	out.open(fileName, fstream::out);
	out << "Picture" << endl;
	out << img->mx << " " << img->my << endl;

	for (int y = 0; y < img->my; y++) {
		for (int x = 0; x < img->mx; x++) {
			out << img->points[y * img->mx + x] << " ";
		}
		out << endl;
	}
	out.close();
}

bool TestCreateImage() {
	Image* pic = new Image;
	createImage(pic, 1, 3);

	if (pic->points[0] == 0 && pic->points[2] == 0 && pic->mx == 1 && pic->my == 2)
		return true;
	return false;
}

bool TestSetPointImage() {
	Image* pic = new Image;
	createImage(pic, 1, 3);
	setPointImage(pic, 1, 0, 245);
	setPointImage(pic, 0, 3, 255);

	if (getPointImage(pic, 1, 0) == 245 && getPointImage(pic, 0, 3) == 255)
		return true;
	return false;
}

bool TestGetPointImage() {
	Image* pic = new Image;
	createImage(pic, 1, 3);
	pic->points[2] = 255;
	if (getPointImage(pic, 1, 2) == 255 && getPointImage(pic, 1, 1) == 0)
		return true;
	return false;
}

bool TestShowImage() {
	Image* pic = new Image;
	createImage(pic, 1, 2);
	setPointImage(pic, 1, 1, 255);
	getPointImage(pic, 1, 1);
	showImage(pic);
	if (pic->points[1 * pic->mx + 1] == 255)
		return true;
	return false;
}

bool TestSaveToPnmFile() {
	Image* pic = new Image;
	createImage(pic, 1, 2);
	setPointImage(pic, 1, 1, 255);
	getPointImage(pic, 1, 1);
	showImage(pic);
	saveToPnmFile(pic, "Test");
	if ("Test" == NULL)
		return false;
	return true;
}

void runTest(bool (*testFunction)(), const std::string& testName) {
	if (testFunction() == 0)
		std::cout << "Test " << testName << " - OK" << std::endl;
	else
		std::cout << "Test " << testName << " - FAIL" << std::endl;
}

int main() {
	Image* img = new Image();
	createImage(img, 6, 10);
	setPointImage(img, 5, 9, 1);
	showImage(img);
	saveToPnmFile(img, "img1.pnm");

	runTest(TestCreateImage, "TestCreateImage");
	runTest(TestGetPointImage, "TestGetPointImage");
	runTest(TestSetPointImage, "TestSetPointImage");
	runTest(TestShowImage, "TestShowImage");
	runTest(TestSaveToPnmFile, "TestSaveToPnmFile");
}