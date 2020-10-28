#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include<opencv2/imgproc.hpp>
using namespace cv;
using namespace std;

// Unsharp Mask 이용해서 샤프닝하기

int main(int argc, char** argv)
{
	Mat image, result, dst, dst1;
	/// Load image
	image = imread(argv[1], 1); // Read the file
	if (image.empty()) { // Check for invalid input
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	// Display the S&P image
	cv::namedWindow("Orignal image");
	cv::imshow("Orignal image", image);

	// sharpen image using "unsharp mask" algorithm
	Mat blurred;
	double sigma = 1, threshold = 5, amount = 1;

	// blurred: 블러링 된 이미지
	GaussianBlur(image, blurred, Size(), sigma, sigma);

	cv::namedWindow("GaussianBlur image");
	cv::imshow("GaussianBlur image", blurred);


	Mat gmask = image - blurred;

	cv::namedWindow("gmask image");
	cv::imshow("gmask image", gmask);

	double k = 1.5;


	// 샤픈드 이미지 뽑아내기
	Mat sharpened = image + k * gmask;



	cv::namedWindow("Sharpened image");
	cv::imshow("Sharpened image", sharpened);
	waitKey(0);
	return 0;
}