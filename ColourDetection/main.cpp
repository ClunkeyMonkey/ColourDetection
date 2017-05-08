#include <opencv2\opencv.hpp>
#include <cstdio>

using namespace cv;
using namespace std;

int main() {
	Mat imageRGB, imageHSV, imageR, imageR1, imageR2, imageY, imageB, imageTest, imageEdge, circles;
	int image = 0;
	int lowH = 0;
	int highH = 179;
	int currentImage = 0;
	bool read = false;
	char s[] = "Image 1.jpg";

	namedWindow("Control", CV_WINDOW_AUTOSIZE);
	cvCreateTrackbar("Image", "Control", &image, 4);
	cvCreateTrackbar("LowH", "Control", &lowH, 179);
	cvCreateTrackbar("HighH", "Control", &highH, 179);

	while (true) {
		if (read == false) {
			s[6] = image + 49;
			imageRGB = imread(s, CV_LOAD_IMAGE_COLOR);
			resize(imageRGB, imageRGB, Size(imageRGB.cols / 5, imageRGB.rows / 5));
			cvtColor(imageRGB, imageHSV, COLOR_BGR2HSV);
			Canny(imageRGB, imageEdge, 20, 75);
			imshow("Edge", imageEdge);

			read = true;
			currentImage = image;
		}
		
		inRange(imageHSV, Scalar(lowH, 0, 0), Scalar(highH, 255, 255), imageTest);
		imshow("Colour", imageTest);

		
		if (waitKey(1) == 27) {
			break;
		}
		if (currentImage != image) {
			read = false;
		}
	}
	
	inRange(imageHSV, Scalar(0, 0, 0), Scalar(4, 255, 255), imageR1);
	inRange(imageHSV, Scalar(170, 0, 0), Scalar(179, 255, 255), imageR2);
	addWeighted(imageR1, 1, imageR2, 1, 0, imageR);
	inRange(imageHSV, Scalar(25, 0, 0), Scalar(60, 255, 255), imageY);
	inRange(imageHSV, Scalar(90, 0, 0), Scalar(130, 255, 255), imageB);

	imwrite("image01RGB.jpg", imageRGB);
	imwrite("image02HSV.jpg", imageHSV);
	imwrite("image03Red.jpg", imageR);
	imwrite("image04Yellow.jpg", imageY);
	imwrite("image05Blue.jpg", imageB);
}