#include <opencv2\opencv.hpp>
#include <cstdio>
#include "json.hpp"

using namespace cv;
using namespace std;
using json = nlohmann::json;

int main() {
	Mat imageRGB, imageGrey, imageHSV, imageR, imageR1, imageR2, imageY, imageB, imageNB;
	Mat imageTest, imageOut, imageEdge, imageCir;

	Mat image1in, image2in, image3in, image4in, image5in;
	Mat image1, image2, image3, image4, image5;
	Mat image1out, image2out, image3out, image4out, image5out;

	vector<Vec3f> circles;
	int image = 0;
	int lowH = 0;
	int highH = 179;
	int lowS = 0;
	int highS = 255;
	int lowV = 0;
	int highV = 255;
	bool read = false;
	char s[] = "Image 5.jpg";
	int val = 10;

	image1in = imread("Image 1.jpg", CV_LOAD_IMAGE_COLOR);
	resize(image1in, image1in, Size(image1in.cols / val, image1in.rows / val));
	cvtColor(image1in, image1, COLOR_BGR2HSV);

	image2in = imread("Image 2.jpg", CV_LOAD_IMAGE_COLOR);
	resize(image2in, image2in, Size(image2in.cols / val, image2in.rows / val));
	cvtColor(image2in, image2, COLOR_BGR2HSV);

	image3in = imread("Image 3.jpg", CV_LOAD_IMAGE_COLOR);
	resize(image3in, image3in, Size(image3in.cols / val, image3in.rows / val));
	cvtColor(image3in, image3, COLOR_BGR2HSV);

	image4in = imread("Image 4.jpg", CV_LOAD_IMAGE_COLOR);
	resize(image4in, image4in, Size(image4in.cols / val, image4in.rows / val));
	cvtColor(image4in, image4, COLOR_BGR2HSV);

	image5in = imread("Image 5.jpg", CV_LOAD_IMAGE_COLOR);

	resize(image5in, image5in, Size(image5in.cols / val, image5in.rows / val));
	cvtColor(image5in, image5, COLOR_BGR2HSV);

	namedWindow("Control", CV_WINDOW_AUTOSIZE);
	//cvCreateTrackbar("Image", "Control", &image, 4);
	cvCreateTrackbar("LowH", "Control", &lowH, 179);
	cvCreateTrackbar("HighH", "Control", &highH, 179);
	cvCreateTrackbar("LowS", "Control", &lowS, 255);
	cvCreateTrackbar("HighS", "Control", &highS, 255);
	cvCreateTrackbar("LowV", "Control", &lowV, 255);
	cvCreateTrackbar("HighV", "Control", &highV, 255);

	while (true) {
		/*if (read == false) {
			s[6] = image + 49;
			imageRGB = imread(s, CV_LOAD_IMAGE_COLOR);
			resize(imageRGB, imageRGB, Size(imageRGB.cols / 4, imageRGB.rows / 4));
			cvtColor(imageRGB, imageGrey, COLOR_BGR2GRAY);
			cvtColor(imageRGB, imageHSV, COLOR_BGR2HSV);
			Canny(imageRGB, imageEdge, 75, 20);


			inRange(imageHSV, Scalar(0, 0, 0), Scalar(4, 255, 255), imageR1);
			inRange(imageHSV, Scalar(160, 0, 0), Scalar(179, 255, 255), imageR2);
			addWeighted(imageR1, 1, imageR2, 1, 0, imageR);
			inRange(imageHSV, Scalar(25, 0, 0), Scalar(70, 255, 255), imageY);
			inRange(imageHSV, Scalar(90, 0, 0), Scalar(130, 255, 255), imageB);
			inRange(imageHSV, Scalar(7, 0, 0), Scalar(20, 255, 255), imageNB);
			imageOut = imageR + imageY + imageB;

			//inRange(imageHSV, Scalar(lowH, 0, 0), Scalar(highH, 255, 255), imageTest);

			dilate(imageOut, imageTest, Mat(), Point(-1, -1), 2, 1, 1);
			erode(imageTest, imageTest, Mat(), Point(-1, -1), 1, 1, 1);

			//imshow("nb", imageNB);

			HoughCircles(imageTest, circles, CV_HOUGH_GRADIENT, 1, 10, 100, 10, cMin, cMax);
			imageCir = Mat(Size(imageTest.cols, imageTest.rows), CV_8UC1);
			cout << circles.size() << endl;
			for (size_t i = 0; i < circles.size(); i++)
			{
				Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
				if ((imageTest.at<uchar>(center.y, center.x) > 128) /*&& (imageNB.at<uchar>(center.y, center.x) < 128)/) {
					int radius = cvRound(circles[i][2]);
					// circle center
					circle(imageTest, center, 3, Scalar(150, 150, 150), -1, 8, 0);
					// circle outline 
					circle(imageTest, center, radius, Scalar(150, 150, 150), 1, 8, 0);
				}
			}
			//imshow("Circles", imageCir);
			imshow("Edge", imageTest);
			read = true;
		}*/

		/*inRange(imageHSV, Scalar(0, 0, 0), Scalar(4, 255, 255), imageR1);
		inRange(imageHSV, Scalar(170, 0, 0), Scalar(179, 255, 255), imageR2);
		imageR = imageR1 + imageR2;
		inRange(imageHSV, Scalar(25, 0, 0), Scalar(60, 255, 255), imageY);
		inRange(imageHSV, Scalar(90, 0, 0), Scalar(130, 255, 255), imageB);
		inRange(imageHSV, Scalar(7, 0, 0), Scalar(20, 255, 255), imageNB);
		imageTest = imageR + imageY + imageB;*/

		inRange(image1, Scalar(lowH, lowS, lowV), Scalar(highH, highS, highV), image1out);
		inRange(image2, Scalar(lowH, lowS, lowV), Scalar(highH, highS, highV), image2out);
		inRange(image3, Scalar(lowH, lowS, lowV), Scalar(highH, highS, highV), image3out);
		inRange(image4, Scalar(lowH, lowS, lowV), Scalar(highH, highS, highV), image4out);
		inRange(image5, Scalar(lowH, lowS, lowV), Scalar(highH, highS, highV), image5out);

		imshow("scr1", image1in);
		imshow("mask1", image1out);

		imshow("scr2", image2in);
		imshow("mask2", image2out);

		imshow("scr3", image3in);
		imshow("mask3", image3out);

		imshow("scr4", image4in);
		imshow("mask4", image4out);

		imshow("scr5", image5in);
		imshow("mask5", image5out);

		if (waitKey(1) == 27) {
			break;
		}
		/*if (waitKey(1) == 32) {
			read = false;
		}*/
	}
	/*imwrite("image01RGB.jpg", imageRGB);
	imwrite("image02HSV.jpg", imageHSV);
	imwrite("image03Red.jpg", imageR);
	imwrite("image04Yellow.jpg", imageY);
	imwrite("image05Blue.jpg", imageB);
	imwrite("image06Circle.jpg", imageCir);
	imwrite("image07Edge.jpg", imageEdge);
	imwrite("image08Out.jpg", imageOut);
	imwrite("image09Test.jpg", imageTest);*/
}