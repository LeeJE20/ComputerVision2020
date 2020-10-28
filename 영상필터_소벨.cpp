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
int main(int argc, char** argv) {
	Mat image, result;
	image = imread("test.jpg", 0);
	if (!image.data)
		return 0;
	// Display the image
	cv::namedWindow("Original Image");
	cv::imshow("Original Image", image);

	// X축에 대한 미분: 수직 엣지 찾음
	// Compute Sobel X derivative
	cv::Mat sobelX;
	// 원본, 결과, 데이터 타입, x축 미분 여부, y축 미분 여부, 스케일, 델타, 보더타입
	cv::Sobel(image, sobelX, CV_8U, 1, 0, 3, 0.4, 128);
	// Display the image
	cv::namedWindow("Sobel X Image");
	cv::imshow("Sobel X Image", sobelX);


	// Y축에 대한 미분: 수평 엣지 찾음
	// Compute Sobel Y derivative
	cv::Mat sobelY;
	cv::Sobel(image, sobelY, CV_8U, 0, 1, 3, 0.4, 128);

	cv::namedWindow("Sobel Y Image");
	cv::imshow("Sobel Y Image", sobelY);



	// Compute norm of Sobel
	cv::Sobel(image, sobelX, CV_16S, 1, 0);
	cv::Sobel(image, sobelY, CV_16S, 0, 1);

	cv::Mat sobel;

	// X, Y 합친다.
	//compute the L1 norm
	sobel = abs(sobelX) + abs(sobelY);

	double sobmin, sobmax;
	cv::minMaxLoc(sobel, &sobmin, &sobmax);


	cv::namedWindow("Sobel");
	cv::imshow("Sobel", sobel);


	cv::Mat sobelImage;
	sobel.convertTo(sobelImage, CV_8U, -255. / sobmax, 255);


	// Display the image
	cv::namedWindow("Sobel Image");
	cv::imshow("Sobel Image", sobelImage);


	// Apply threshold to Sobel norm (low threshold value)
	cv::Mat sobelThresholded;
	cv::threshold(sobelImage, sobelThresholded, 225, 255, cv::THRESH_BINARY);


	// Display the image
	cv::namedWindow("Binary Sobel Image (low)");
	cv::imshow("Binary Sobel Image (low)", sobelThresholded);
	waitKey(0);
	return 0;
}