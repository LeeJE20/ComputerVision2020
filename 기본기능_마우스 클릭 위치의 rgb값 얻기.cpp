#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include<opencv2/imgproc.hpp>
using namespace cv;
using namespace std;

// 마우스 클릭 위치의 rgb값 얻기


void mouseEvent(int evt, int x, int y, int flags, void* param) {
	Mat* rgb = (Mat*)param;
	if (evt == EVENT_LBUTTONDOWN)
	{
		printf("%d %d: %d, %d, %d\n",
			x, y,
			(int)(*rgb).at<Vec3b>(y, x)[0],
			(int)(*rgb).at<Vec3b>(y, x)[1],
			(int)(*rgb).at<Vec3b>(y, x)[2]);
	}
}


int main(int argc, char** argv)
{
	Mat image, result;
	image = imread("test.jpg", IMREAD_COLOR); // Read the file 


	if (image.empty()) // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
	//set the callback function for any mouse event
	setMouseCallback("Display window", mouseEvent, &image);
	imshow("Display window", image); // Show our image inside it.
	waitKey(0); // Wait for a keystroke in the window
	return 0;
}

