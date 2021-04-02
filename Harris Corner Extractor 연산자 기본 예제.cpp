
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

// Harris Corner Extractor 연산자 기본 예제

int main(int argc, char** argv)
{
	// Read input image
	cv::Mat image = cv::imread(argv[1], 0);
	if (!image.data) return 0;
	// Display the image
	cv::namedWindow("Original Image");
	cv::imshow("Original Image", image);
	// Detect Harris Corners
	cv::Mat cornerStrength;
	cv::cornerHarris(image, cornerStrength, // Corner score 계산
		3, // neighborhood size
		3, // aperture size
		0.01); // Harris parameter
		// threshold the corner strengths
	cv::Mat harrisCorners;
	double threshold = 0.0001; // C: corner value
	cv::threshold(cornerStrength, harrisCorners, threshold, 255, cv::THRESH_BINARY_INV); // 큰 Score만 선정
	// Display the corners
	cv::namedWindow("Harris Corner Map");
	cv::imshow("Harris Corner Map", harrisCorners);

	threshold = 0.001; // C: corner value
	cv::threshold(cornerStrength, harrisCorners, threshold, 255, cv::THRESH_BINARY_INV); // 큰 Score만 선정
	// Display the corners
	cv::namedWindow("th = 0.001");
	cv::imshow("th = 0.001", harrisCorners);

	threshold = 0.01; // C: corner value
	cv::threshold(cornerStrength, harrisCorners, threshold, 255, cv::THRESH_BINARY_INV); // 큰 Score만 선정
	// Display the corners
	cv::namedWindow("th = 0.01");
	cv::imshow("th = 0.01", harrisCorners);


	cv::waitKey();
	return 0;
}