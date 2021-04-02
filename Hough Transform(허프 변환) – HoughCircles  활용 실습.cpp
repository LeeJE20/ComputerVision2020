
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

//Hough Transform(허프 변환) – HoughCircles  활용 실습

int main(int argc, char** argv)
{
	Mat image, result;
	// Detect circles
	image = cv::imread(argv[1], 0);
	//result = image.clone();
	cv::namedWindow("Original");
	cv::imshow("Original", image);

	cv::GaussianBlur(image, image, cv::Size(5, 5), 1.5);
	std::vector<cv::Vec3f> circles;
	cv::HoughCircles(image, circles, HOUGH_GRADIENT,
		2, // accumulator resolution (size of the image / 2)
		50, // minimum distance between two circles
		200, // Canny high threshold
		100, // minimum number of votes
		25, 100); // min and max radius
	std::cout << "Circles: " << circles.size() << std::endl;

	// Draw the circles
	result = cv::imread(argv[1], 1);
	std::vector<cv::Vec3f>::const_iterator itc = circles.begin();
	while (itc != circles.end()) {
		cv::circle(result,
			cv::Point((*itc)[0], (*itc)[1]), // circle centre
			(*itc)[2], //circle radius
			cv::Scalar(255), // color
			2); // thickness
		++itc;
	}
	cv::namedWindow("Detected Circles");
	cv::imshow("Detected Circles", result);
	cv::waitKey();
	return 0;
}