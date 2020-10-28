#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include<opencv2/imgproc.hpp>
using namespace cv;
using namespace std;

#pragma warning(disable : 4996)

// 영상 위에 임의의 text 표시해주기

// Global Variables
const int alpha_slider_max = 255;
int alpha_slider;
double alpha;
double beta;
Mat image1, image2, dst;
void on_trackbar(int, void*);



int main(int argc, char** argv)
{
	image1 = imread("test.jpg", 1);
	image2 = imread("test1.jpg", 1);
	namedWindow("Display Blend");



	/// Create Trackbars
	char TrackbarName[50];
	sprintf(TrackbarName, "Alpha x %d", alpha_slider_max);
	// 트랙바 이름, 윈도우, 트랙바 값, 트랙바 최대값, 온트랙바 함수에 기능 구현
	createTrackbar(TrackbarName, "Display Blend", &alpha_slider, alpha_slider_max, on_trackbar);
	/// Show some stuff
	// 알파 슬라이더 초기값 0
	on_trackbar(alpha_slider, 0);



	waitKey(0);// Wait for a keystroke in the window
	destroyWindow("Display Blend");// 또는 destroyWindowall();
	return 0;
}


/**
* @function on_trackbar
* @brief Callback for trackbar
*/
void on_trackbar(int, void*)
{
	// 알파 슬라이더 값으로 이진화
	threshold(image1, dst, alpha_slider, 255, 0);
	imshow("Display Blend", dst);
}