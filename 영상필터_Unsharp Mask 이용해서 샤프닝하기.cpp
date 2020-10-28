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
	image = imread("test.jpg", 1); // Read the file
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

	// threshold보다 작은건 죽이고 큰거만 살리기. 여기 줄은 없어도 됨
	Mat lowContrastMask = abs(image - blurred) < threshold;

	cv::namedWindow("lowContrastMask image");
	cv::imshow("lowContrastMask image", lowContrastMask);

	// 샤픈드 이미지 뽑아내기
	Mat sharpened = image * (1 + amount) + blurred * (-amount);

	// image를 sharpened로 카피
	// 마스크가 0이면 카피하지 않는다.
	image.copyTo(sharpened, lowContrastMask);


	cv::namedWindow("Sharpened image");
	cv::imshow("Sharpened image", sharpened);
	waitKey(0);
	return 0;
}