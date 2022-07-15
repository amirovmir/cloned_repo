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
	string color;
	vector<Point2f> dest;
	vector<Point2f> src;
	Mat K;
public:
	vector<vector<Point>> contours;
	VideoFindColor() {
		src.push_back(Point2f(0, 0));
		src.push_back(Point2f(100, 0));
		src.push_back(Point2f(0, 100));
		src.push_back(Point2f(100, 100));
		dest.push_back(Point2f(351, 315));
		dest.push_back(Point2f(125, 135));
		dest.push_back(Point2f(205, 215));
		dest.push_back(Point2f(302, 310));
	};
	~VideoFindColor() {};
	void detectingColor(Mat image, string color, Scalar minColor, Scalar maxColor, vector<vector<Point>> &contours, ofstream &fout);
	void findContrastingColor(Mat image, vector<vector<Point>> &contours);
	void findHomograph(Mat im_src, Mat im_dest);
	void warpImage(Mat img);
	int run();
};

void VideoFindColor::detectingColor(Mat image, string color, Scalar minColor, Scalar maxColor, vector<vector<Point>> &contours, ofstream &fout) {
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
		dest.push_back(Point2f(pt1.x, pt1.y));
		dest.push_back(Point2f(pt2.x, pt1.y));
		dest.push_back(Point2f(pt1.x, pt2.y));
		dest.push_back(Point2f(pt2.x, pt2.y));
		if (rect.width >= 10 && rect.width <=1000 && rect.height >= 10 && rect.height <=1000){
		rectangle(image, pt1, pt2, CV_RGB(255,0,0), 1);
		pt1.x = rect.x + rect.width/2;
		pt1.y = rect.y + rect.height/2;
		rectangle(image, pt1, pt1, CV_RGB(0,255,0), 5);
		fout << color << " object coordinates: " << pt1 << endl;
		}
	}
}

void VideoFindColor::findContrastingColor (Mat image, vector<vector<Point>> &contours) {
	ofstream fout("data.txt");
	detectingColor(image, "Blue", blueMin, blueMax, contours, fout);
	detectingColor(image, "Red", redMin, redMax, contours, fout);
	detectingColor(image, "Green", greenMin, greenMax, contours, fout);
	detectingColor(image, "Yellow", yellowMin, yellowMax, contours, fout);
};

int VideoFindColor::run() {
	VideoCapture cap(0);
	if (!cap.isOpened()) {
		cout << "No camera" << endl;
		return EXIT_FAILURE;
	}

	Mat source;
	namedWindow("source", WINDOW_AUTOSIZE);
	while (1) {
		cap >> source;
		resize(source,source,Size(900,900));
		findContrastingColor(source, contours);
		if (waitKey(33) == 27) break;
		imshow("source", source);
		findHomograph(source, source);
	};
	return 0;
};

void VideoFindColor::findHomograph(Mat im_src, Mat im_dest) {
	Mat H = findHomography(dest, src);
	Mat im_out;
	warpPerspective(im_src, im_out, H, im_dest.size());
	imshow("Warped source image", im_out);
}

void VideoFindColor::warpImage(Mat img) {
	Mat img_warp;
	Mat H = findHomography(src, img);
	warpPerspective(img, img_warp, H, img.size());
	imshow("Warp Image", img_warp);
}

int main(){
	VideoFindColor img;
	img.run();
	return 0;
}
