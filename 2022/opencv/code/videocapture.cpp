#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace cv;
using namespace std;

void findContrastingColor(Mat source, Scalar minColor, Scalar maxColor, ofstream* file) {
	vector <vector<Point>> contours;
	Mat HSV, object;
	cvtColor(source, HSV, COLOR_BGR2HSV);
	medianBlur(HSV, HSV, 13);
	inRange(HSV, minColor, maxColor, object);
	findContours(object, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	Mat source_copy = source.clone();
	for (int i = 0; i < contours.size(); i++) {
		Rect rect = boundingRect(contours[i]);
		Point pt1, pt2;
		pt1.x = rect.x;
		pt1.y = rect.y;
		pt2.x = rect.x + rect.width;
		pt2.y = rect.y + rect.height;
		if (rect.width >= 50 && rect.width <= 500 && rect.height >= 10 && rect.height <= 500) {
			rectangle(source, pt1, pt2, CV_RGB(255, 0, 0), 1);
			pt1.x = rect.x + rect.width / 2;
			pt1.y = rect.y + rect.height / 2;
			rectangle(source, pt1, pt1, CV_RGB(0, 255, 0), 5);
			cout << pt1;
			*file << pt1.x << " " << pt1.y << endl;
		}
	}
	imshow("source", source);
	imshow("object", object);
}

int run() {
	VideoCapture cap(0);
	if (!cap.isOpened()) {
		cout << "No camera" << endl;
		return EXIT_FAILURE;
	}
	Mat source;
	namedWindow("source");
	namedWindow("object");
	Scalar blueMin = Scalar(95, 187, 93);
	Scalar blueMax = Scalar(125, 252, 255);

	ofstream fout("data.txt");

	while (1) {
		cap >> source;
		findContrastingColor(source, blueMin, blueMax, &fout);
		if (waitKey(33) == 27) break;
	}
	fout.close();
}

int main() {
	run();
	return 0;
}
