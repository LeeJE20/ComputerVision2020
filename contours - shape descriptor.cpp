
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

#include <stdio.h>

using namespace std;
using namespace cv;

#define PI 3.141592

//shape descriptor

int main()
{
	// Read input binary image
	cv::Mat image = cv::imread("binaryGroup.bmp", 0);
	if (!image.data)
		return 0;
	cv::namedWindow("Binary Image");
	cv::imshow("Binary Image", image);
	// Get the contours of the connected components
	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(image,
		contours, // a vector of contours
		RETR_EXTERNAL, // retrieve the external contours
		CHAIN_APPROX_NONE); // retrieve all pixels of each contours

	// draw black contours on white image
	cv::Mat result(image.size(), CV_8U, cv::Scalar(255));
	cv::drawContours(result, contours,
		-1, // draw all contours
		cv::Scalar(0), // in black
		2); // with a thickness of 2
	cv::namedWindow("Contours");
	cv::imshow("Contours", result);
	// Eliminate too short or too long contours
	int cmin = 100; // minimum contour length
	int cmax = 1000; // maximum contour length
	std::vector<std::vector<cv::Point>>::const_iterator itc = contours.begin();
	while (itc != contours.end()) {
		if (itc->size() - 1 < cmin || itc->size() - 1 > cmax)
			itc = contours.erase(itc);
		else
			++itc;
	}


	// draw contours on the original image
	cv::Mat original = cv::imread("group.jpg", 1);
	cv::drawContours(original, contours,
		-1, // draw all contours
		cv::Scalar(255, 255, 255), // in white
		2); // with a thickness of 2
	cv::namedWindow("Contours on Animals");
	cv::imshow("Contours on Animals", original);

	//std::cout << " Step-2) Press any key to detect shape descriptor...!! " << std::endl;
	//cv::waitKey(0);
	image = cv::imread("binaryGroup.bmp", 0);
	// testing the bounding box


	itc = contours.begin();
	while (itc != contours.end()) {
		cv::Rect r0 = cv::boundingRect(cv::Mat(*itc));
		cv::rectangle(original, r0, cv::Scalar(0), 2);
		++itc;
	}




	cv::namedWindow("Some Shape descriptors");
	cv::imshow("Some Shape descriptors", original);


	cv::waitKey(0);
	return 0;
}