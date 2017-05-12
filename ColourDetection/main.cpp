#include <opencv2\opencv.hpp>
#include "json.hpp"

using namespace cv;
using namespace std;
using json = nlohmann::json;

void getCircles(json vals, char* s);
void getRed(Mat* imageIn, Mat* image, json vals);
void getYel(Mat* imageIn, Mat* image, json vals);
void getBlu(Mat* imageIn, Mat* image, json vals);

int main() {
	json values = {
		{ "Image 1.jpg",{
			{ "R",{ { "d1",1 },{ "e1",1 },{ "d2",4 },{ "e2",1 },{ "gaus",11 },{ "cMin",70 },{ "dist",20 } } },
			{ "B",{ { "d1",4 },{ "e1",2 },{ "d2",2 },{ "e2",1 },{ "gaus",9 },{ "cMin",56 },{ "dist",30 } } },
			{ "Y",{ { "d1",2 },{ "e1",1 },{ "d2",2 },{ "e2",1 },{ "gaus",11 },{ "cMin",56 },{ "dist",30 } } } } },
		{ "Image 2.jpg",{
			{ "R",{ { "d1",4 },{ "e1",1 },{ "d2",4 },{ "e2",2 },{ "gaus",11 },{ "cMin",70 },{ "dist",18 } } },
			{ "B",{ { "d1",2 },{ "e1",2 },{ "d2",3 },{ "e2",1 },{ "gaus",9 },{ "cMin",56 },{ "dist",30 } } },
			{ "Y",{ { "d1",1 },{ "e1",4 },{ "d2",1 },{ "e2",2 },{ "gaus",9 },{ "cMin",56 },{ "dist",17 } } } } },
		{ "Image 3.jpg",{
			{ "R",{ { "d1",4 },{ "e1",1 },{ "d2",4 },{ "e2",1 },{ "gaus",11 },{ "cMin",56 },{ "dist",20 } } },
			{ "B",{ { "d1",4 },{ "e1",1 },{ "d2",3 },{ "e2",1 },{ "gaus",9 },{ "cMin",56 },{ "dist",21 } } },
			{ "Y",{ { "d1",1 },{ "e1",2 },{ "d2",1 },{ "e2",1 },{ "gaus",9 },{ "cMin",56 },{ "dist",23 } } } } },
		{ "Image 4.jpg",{
			{ "R",{ { "d1",1 },{ "e1",1 },{ "d2",4 },{ "e2",2 },{ "gaus",11 },{ "cMin",56 },{ "dist",20 } } },
			{ "B",{ { "d1",4 },{ "e1",1 },{ "d2",2 },{ "e2",1 },{ "gaus",9 },{ "cMin",56 },{ "dist",21 } } },
			{ "Y",{ { "d1",1 },{ "e1",2 },{ "d2",1 },{ "e2",1 },{ "gaus",9 },{ "cMin",56 },{ "dist",24 } } } } },
		{ "Image 5.jpg",{
			{ "R",{ { "d1",2 },{ "e1",3 },{ "d2",3 },{ "e2",2 },{ "gaus",11 },{ "cMin",70 },{ "dist",22 } } },
			{ "B",{ { "d1",1 },{ "e1",2 },{ "d2",1 },{ "e2",1 },{ "gaus",9 },{ "cMin",56 },{ "dist",22 } } },
			{ "Y",{ { "d1",1 },{ "e1",2 },{ "d2",1 },{ "e2",1 },{ "gaus",9 },{ "cMin",56 },{ "dist",26 } } } } }
	};

	Mat image1, image2, image3, image4, image5;
	char s[] = "Image x.jpg";
	int i = 0;

	for (i = 0; i < 5; i++) {
		s[6] = i + 49;
		getCircles(values[s], s);
	}
}

void getCircles(json vals, char* s) {
	Mat imageIn, image;
	char outName[] = "Image x out.jpg";

	imageIn = imread(s, CV_LOAD_IMAGE_COLOR);
	cvtColor(imageIn, image, COLOR_BGR2HSV);

	getRed(&imageIn, &image, vals["R"]);
	getYel(&imageIn, &image, vals["Y"]);
	getBlu(&imageIn, &image, vals["B"]);

	outName[6] = s[6];
	imwrite(outName, imageIn);
}

void getRed(Mat* imageIn, Mat* image, json vals) {
	Mat redTmp, imageR;
	vector<Vec3f> circles;

	inRange(*image, Scalar(170, 180, 120), Scalar(178, 215, 255), imageR);
	inRange(*image, Scalar(0, 132, 50), Scalar(5, 255, 180), redTmp);
	imageR = imageR + redTmp;

	dilate(imageR, imageR, Mat(), Point(-1, -1), vals["d1"], 1, 1);
	erode(imageR, imageR, Mat(), Point(-1, -1), vals["e1"], 1, 1);
	dilate(imageR, imageR, Mat(), Point(-1, -1), vals["d2"], 1, 1);
	erode(imageR, imageR, Mat(), Point(-1, -1), vals["e2"], 1, 1);

	GaussianBlur(imageR, imageR, Size(vals["gaus"], vals["gaus"]), -1, -1);

	HoughCircles(imageR, circles, CV_HOUGH_GRADIENT, 1, vals["cMin"], 200, vals["dist"], 30, 110);

	for (size_t i = 0; i < circles.size(); i++) {
		Point c(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int r = cvRound(circles[i][2]);
		circle(*imageIn, c, 10, Scalar(255, 255, 0), -1, 8, 0);
		circle(*imageIn, c, r, Scalar(0, 0, 255), 10, 8, 0);
	}
}

void getYel(Mat* imageIn, Mat* image, json vals) {
	Mat imageY;
	vector<Vec3f> circles;

	inRange(*image, Scalar(25, 50, 106), Scalar(80, 255, 255), imageY);

	dilate(imageY, imageY, Mat(), Point(-1, -1), vals["d1"], 1, 1);
	erode(imageY, imageY, Mat(), Point(-1, -1), vals["e1"], 1, 1);
	dilate(imageY, imageY, Mat(), Point(-1, -1), vals["d2"], 1, 1);
	erode(imageY, imageY, Mat(), Point(-1, -1), vals["e2"], 1, 1);

	GaussianBlur(imageY, imageY, Size(vals["gaus"], vals["gaus"]), -1, -1);

	HoughCircles(imageY, circles, CV_HOUGH_GRADIENT, 1, vals["cMin"], 200, vals["dist"], 30, 110);

	for (size_t i = 0; i < circles.size(); i++) {
		Point c(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int r = cvRound(circles[i][2]);
		circle(*imageIn, c, 10, Scalar(255, 0, 155), -1, 8, 0);
		circle(*imageIn, c, r, Scalar(0, 255, 100), 10, 8, 0);
	}
}

void getBlu(Mat* imageIn, Mat* image, json vals) {
	Mat imageB;
	vector<Vec3f> circles;

	inRange(*image, Scalar(105, 175, 30), Scalar(120, 255, 240), imageB);

	dilate(imageB, imageB, Mat(), Point(-1, -1), vals["d1"], 1, 1);
	erode(imageB, imageB, Mat(), Point(-1, -1), vals["e1"], 1, 1);
	dilate(imageB, imageB, Mat(), Point(-1, -1), vals["d2"], 1, 1);
	erode(imageB, imageB, Mat(), Point(-1, -1), vals["e2"], 1, 1);

	GaussianBlur(imageB, imageB, Size(vals["gaus"], vals["gaus"]), -1, -1);

	HoughCircles(imageB, circles, CV_HOUGH_GRADIENT, 1, vals["cMin"], 200, vals["dist"], 30, 110);

	for (size_t i = 0; i < circles.size(); i++) {
		Point c(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int r = cvRound(circles[i][2]);
		circle(*imageIn, c, 10, Scalar(0, 255, 255), -1, 8, 0);
		circle(*imageIn, c, r, Scalar(255, 0, 0), 10, 8, 0);
	}
}