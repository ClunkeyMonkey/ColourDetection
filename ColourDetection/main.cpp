#include <opencv2\opencv.hpp>
#include <cstdio>

using namespace cv;
using namespace std;

int main() {
	Mat imageRGB, imageGrey, imageHSV, imageR, imageR1, imageR2, imageY, imageB, imageTest, imageEdge, imageCir;
	vector<Vec3f> circles;
	int image = 0;
	int lowH = 90;
	int highH = 130;
	int cMin = 0;
	int cMax = 40;
	bool read = false;
	char s[] = "Image 5.jpg";

	/*namedWindow("Control", CV_WINDOW_AUTOSIZE);
	cvCreateTrackbar("Image", "Control", &image, 4);
	cvCreateTrackbar("LowH", "Control", &lowH, 179);
	cvCreateTrackbar("HighH", "Control", &highH, 179);
	cvCreateTrackbar("cMin", "Control", &cMin, 200);
	cvCreateTrackbar("cMax", "Control", &cMax, 300);

	while (true) {
		if (read == false) {
			s[6] = image + 49;
			imageRGB = imread(s, CV_LOAD_IMAGE_COLOR);
			resize(imageRGB, imageRGB, Size(imageRGB.cols / 5, imageRGB.rows / 5));
			cvtColor(imageRGB, imageGrey, COLOR_BGR2GRAY);
			cvtColor(imageRGB, imageHSV, COLOR_BGR2HSV);
			Canny(imageRGB, imageEdge, 75, 20);
			
			GaussianBlur(imageEdge, imageEdge, Size(5, 5), 0, 0);
			imshow("Edge", imageEdge);
			HoughCircles(imageEdge, circles, CV_HOUGH_GRADIENT, 1, imageEdge.rows / 16, 75, 20, cMin, cMax);
			imageCir = Mat(Size(imageRGB.cols, imageRGB.rows), CV_8UC1);
			cout << circles.size() << endl;
			for (size_t i = 0; i < circles.size(); i++)
			{
				Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
				int radius = cvRound(circles[i][2]);
				// circle center
				circle(imageCir, center, 3, Scalar(0, 255, 0), -1, 8, 0);
				// circle outline
				circle(imageCir, center, radius, Scalar(0, 0, 255), 1, 8, 0);
			}
			imshow("Circles", imageCir);
			read = true;
		}
		
		inRange(imageHSV, Scalar(lowH, 0, 0), Scalar(highH, 255, 255), imageTest);
		imshow("Colour", imageTest);

		
		if (waitKey(1) == 27) {
			break;
		}
		if (waitKey(1) == 32) {
			read = false;
		}
	}*/
	
	imageRGB = imread(s /*"circles.jpg"*/, CV_LOAD_IMAGE_COLOR);
	//resize(imageRGB, imageRGB, Size(imageRGB.cols / 4, imageRGB.rows / 4));
	cvtColor(imageRGB, imageGrey, COLOR_BGR2GRAY);
	cvtColor(imageRGB, imageHSV, COLOR_BGR2HSV);
	Canny(imageRGB, imageEdge, 75, 20);

	inRange(imageHSV, Scalar(0, 0, 0), Scalar(4, 255, 255), imageR1);
	inRange(imageHSV, Scalar(170, 0, 0), Scalar(179, 255, 255), imageR2);
	addWeighted(imageR1, 1, imageR2, 1, 0, imageR);
	inRange(imageHSV, Scalar(25, 0, 0), Scalar(60, 255, 255), imageY);
	inRange(imageHSV, Scalar(90, 0, 0), Scalar(130, 255, 255), imageB);
	
	GaussianBlur(imageR, imageR, Size(7, 7), 0, 0);
	HoughCircles(imageR, circles, CV_HOUGH_GRADIENT, 1, imageEdge.rows / 16, 75, 20, 0, 150);

	imageCir = Mat(Size(imageRGB.cols, imageRGB.rows), CV_8UC1);
	cout << circles.size() << endl;
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int val = imageR.at<uchar>(center.y, center.x);
		if (val > 200) {
			int radius = cvRound(circles[i][2]);
			// circle center
			circle(imageCir, center, 3, Scalar(0, 255, 0), -1, 8, 0);
			// circle outline
			circle(imageCir, center, radius, Scalar(0, 0, 255), 3, 8, 0);
		}
	}

	imwrite("image01RGB.jpg", imageRGB);
	imwrite("image02HSV.jpg", imageHSV);
	imwrite("image03Red.jpg", imageR);
	imwrite("image04Yellow.jpg", imageY);
	imwrite("image05Blue.jpg", imageB);
	imwrite("image06Circle.jpg", imageCir);
}