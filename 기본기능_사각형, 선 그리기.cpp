#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include<opencv2/imgproc.hpp>
using namespace cv;
using namespace std;

// 사각형, 선 그리기


int main(int argc, char** argv)
{
	//--OpenCV 2.x 구현 --//
	// 스칼라: 색상 (노란색). BGR
	Mat image(512, 512, CV_8UC3, Scalar(0, 255, 255));

	// 점, 점, 색깔(빨강)
	rectangle(image, Point(100, 100), Point(400, 400), CV_RGB(255, 0, 0));
	line(image, Point(400, 100), Point(100, 400), Scalar(0, 255, 0));

	// 점, 점, 색깔(초록), 두께, 라인타입, 시프트
	line(image, Point(400, 100), Point(100, 400), Scalar(0, 255, 0), 2, 8, 1);
	rectangle(image, Point(400 / 2, 100 / 2), Point(100 / 2, 400 / 2), CV_RGB(0, 0, 255));
	namedWindow("Drawing Graphics");
	imshow("Drawing Graphics", image);
	waitKey(0);// Wait for a keystroke in the window

	return 0;
}