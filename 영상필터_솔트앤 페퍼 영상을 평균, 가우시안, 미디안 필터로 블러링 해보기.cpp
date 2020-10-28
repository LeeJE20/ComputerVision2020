#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include<opencv2/imgproc.hpp>
using namespace cv;
using namespace std;

// 솔트앤 페퍼 영상을 평균, 가우시안, 미디안 필터로 블러링 해보기

void salt(Mat& img, int n); // 잡음 추가 함수 선언

// argument를 입력 받게 하자!
// argument 첫번째, 두번째.. 갖고옴
int main(int argc, char** argv)
{
	Mat image, result, dst, dst1;
	/// Load image
	image = imread(argv[1], 1); // Read the file
	if (image.empty()) { // Check for invalid input
		cout << "Could not open or find the image"
			<< std::endl;
		return -1;
	}


	//솔트앤 페퍼 영상 만들기
	// make a noise image
	salt(image, 30000);
	// Display the S&P image
	cv::namedWindow("S&P Image");
	cv::imshow("S&P Image", image);


	//평균 필터
	// Blur the image with a mean filter
	cv::blur(image, result, cv::Size(5, 5));
	// Display the blurred image
	cv::namedWindow("Mean filtered S&P Image");
	cv::imshow("Mean filtered S&P Image", result);
	


	//가우시안
	// Gaussian Blur the image
	GaussianBlur(image, result, cv::Size(5, 5), 1.5);
	// Display the blurred image
	namedWindow("Gaussian filtered Image");
	imshow("Gaussian filtered Image", result);



	//미디안 필터
	// Applying a median filter
	cv::medianBlur(image, result, 5);
	// Display the blurred image
	cv::namedWindow("Median filtered S&P Image");
	cv::imshow("Median filtered S&P Image", result);
	waitKey(0);
	return 0;


}

void salt(Mat& img, int n)
{
	for (int k = 0; k < n; k++) {
		int i = rand() % img.cols;
		int j = rand() % img.rows;
		if (img.channels() == 1) { // Gray scale image
			img.at<uchar>(j, i) = 255;
		}
		else if (img.channels() == 3) { // Color image
			img.at<Vec3b>(j, i)[0] = 255;
			img.at<Vec3b>(j, i)[1] = 255;
			img.at<Vec3b>(j, i)[2] = 255;
		}
	}
}
