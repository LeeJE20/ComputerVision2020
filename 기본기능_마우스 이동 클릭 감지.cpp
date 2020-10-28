#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include<opencv2/imgproc.hpp>
using namespace cv;
using namespace std;

// 버튼 이벤트 기능 구현


void my_mouse_callback(int event, int x, int y, int flags, void* param); // 함수 선언

int main(int argc, char** argv)
{
	//--- 마우스 이벤트 구현 ---//
	int i, j, k;
	Mat image;
	image.create(500, 500, CV_8UC3);
	namedWindow("Main");
	for (i = 0; i < 500; i++) {
		for (j = 0; j < 500; j++) {
			for (k = 0; k < 3; k++) {
				Vec3b& intensity = image.at<Vec3b>(j, i);
				intensity.val[k] = 0;
			}
		}
	}

	setMouseCallback("Main", my_mouse_callback, &image);
	imshow("Main", image);
	waitKey(0); // Wait for anu user’s key stroke….!!!!!
	return 0;
}

//--- 마우스 이벤트 구현함 --//
void my_mouse_callback(int event, int x, int y, int flags, void* param) {
	int thickness = -1;
	int lineType = 8;
	if (event == EVENT_LBUTTONDOWN) {
		cout << "Left button has been clicked (" << x << "," << y << ")" << std::endl;
	}
	else if (event == EVENT_RBUTTONDOWN) {
		cout << "Right button has been clicked (" << x << "," << y << ")" << std::endl;
	}
	else if (event == EVENT_MOUSEMOVE) {
		cout << "Mouse has been moved (" << x << "," << y << ")" << std::endl;
	}
}
