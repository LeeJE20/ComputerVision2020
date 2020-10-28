#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include<opencv2/imgproc.hpp>
using namespace cv;
using namespace std;

// filter2D: 사용자가 직접 커널 설계


// argument를 입력 받게 하자!
// argument 첫번째, 두번째.. 갖고옴
int main(int argc, char** argv)
{
	Mat image, result;
	image = imread("test.jpg");


	// 샤프닝된다 (합이 1)
	// 커널 0으로 초기화
	// Construct kernel (all entries initialized to 0)
	Mat kernel(3, 3, CV_32F, Scalar(0));
	// assigns kernel values
	kernel.at<float>(1, 1) = 5.0;
	kernel.at<float>(0, 1) = -1.0;
	kernel.at<float>(2, 1) = -1.0;
	kernel.at<float>(1, 0) = -1.0;
	kernel.at<float>(1, 2) = -1.0;

	//filter the image
	filter2D(image, result, image.depth(), kernel);

	/// Create window
	namedWindow("Original Image");
	imshow("Original Image", image);
	/// Create window
	namedWindow("Filtered image");
	imshow("Filtered image", result);
	waitKey(0);
	return 0;
}