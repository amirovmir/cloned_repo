#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace cv;
using namespace std;

class VideoFindColor {
	Mat image;
	Scalar blueMin = Scalar(59, 32, 195);
	Scalar blueMax = Scalar(114, 115, 244);
	Scalar redMin = Scalar(86,62,130);
	Scalar redMax = Scalar(175,186,255);
	Scalar greenMin = Scalar(37,74,195);
	Scalar greenMax = Scalar(89,136,255);
	Scalar yellowMin = Scalar(0,121,163);
	Scalar yellowMax = Scalar(52,193,244);
	ofstream fout;
	string color;
public:
	vector<vector<Point>> contours;
	VideoFindColor() {};
	~VideoFindColor() {};
	void detectingColor(Mat image, string color, Scalar minColor, Scalar maxColor, vector<vector<Point>> &contours);
	void writingToFile(Point &pt, string color);
	void findContrastingColor(Mat image, vector<vector<Point>> &contours);
	int run();
};

void VideoFindColor::detectingColor(Mat image, string color, Scalar minColor, Scalar maxColor, vector<vector<Point>> &contours) {
	Mat hsv;
	cvtColor(image, hsv, COLOR_BGR2HSV);
	medianBlur(hsv,hsv,13);
	Mat clone_source(image.size(), CV_8U);
	inRange(hsv, minColor, maxColor, clone_source);
	imshow(color, clone_source);
	findContours(clone_source, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	for(int i = 0; i < contours.size(); i++){
		Rect rect = boundingRect(contours[i]);
		Point pt1, pt2;
		pt1.x = rect.x;
		pt1.y = rect.y;
		pt2.x = rect.x + rect.width;
		pt2.y = rect.y + rect.height;
		if (rect.width >= 50 && rect.width <=500 && rect.height >= 10 && rect.height <=500){
		rectangle(image, pt1, pt2, CV_RGB(255,0,0), 1);
		pt1.x = rect.x + rect.width/2;
		pt1.y = rect.y + rect.height/2;
		rectangle(image, pt1, pt1, CV_RGB(0,255,0), 5);
		writingToFile(pt1, color);
		}
	}
}

void VideoFindColor::writingToFile(Point &pt, string color) {
	fout << color << " object coordinates: " << pt << endl;
}

void VideoFindColor::findContrastingColor (Mat image, vector<vector<Point>> &contours){
	fout.open("data.txt");
	detectingColor(image, "Blue", blueMin, blueMax, contours);
	detectingColor(image, "Red", redMin, redMax, contours);
	detectingColor(image, "Green", greenMin, greenMax, contours);
	detectingColor(image, "Yellow", yellowMin, yellowMax, contours);
};

int VideoFindColor::run() {
	VideoCapture cap(0);
	if (!cap.isOpened()) {
		cout << "No camera" << endl;
		return EXIT_FAILURE;
	}
	Mat source;
	namedWindow("source");
	while (1) {
		cap >> source;
		findContrastingColor(source, contours);
		if (waitKey(33) == 27) break;
		imshow("source", source);
	};
	fout.close();
	return 0;
};

int main(){
	VideoFindColor img;
	img.run();
	return 0;
}
