#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include<opencv2/imgproc.hpp>
using namespace cv;
using namespace std;

// filter2D: ����ڰ� ���� Ŀ�� ����


// argument�� �Է� �ް� ����!
// argument ù��°, �ι�°.. �����
int main(int argc, char** argv) {
	Mat image, result;
	image = imread("test.jpg", 0);
	if (!image.data)
		return 0;
	// Display the image
	cv::namedWindow("Original Image");
	cv::imshow("Original Image", image);

	// X�࿡ ���� �̺�: ���� ���� ã��
	// Compute Sobel X derivative
	cv::Mat sobelX;
	// ����, ���, ������ Ÿ��, x�� �̺� ����, y�� �̺� ����, ������, ��Ÿ, ����Ÿ��
	cv::Sobel(image, sobelX, CV_8U, 1, 0, 3, 0.4, 128);
	// Display the image
	cv::namedWindow("Sobel X Image");
	cv::imshow("Sobel X Image", sobelX);


	// Y�࿡ ���� �̺�: ���� ���� ã��
	// Compute Sobel Y derivative
	cv::Mat sobelY;
	cv::Sobel(image, sobelY, CV_8U, 0, 1, 3, 0.4, 128);

	cv::namedWindow("Sobel Y Image");
	cv::imshow("Sobel Y Image", sobelY);



	// Compute norm of Sobel
	cv::Sobel(image, sobelX, CV_16S, 1, 0);
	cv::Sobel(image, sobelY, CV_16S, 0, 1);

	cv::Mat sobel;

	// X, Y ��ģ��.
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