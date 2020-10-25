#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include<opencv2/imgproc.hpp>
using namespace cv;
using namespace std;

// 트랙바 활용 쓰레스홀드


///--- Global variables----///
int threshold_value = 0;
int threshold_type = 3;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;
Mat image, src_gray, dst;
const char* window_name = "Threshold Demo";
const char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
const char* trackbar_value = "Value";
void Threshold_Demo(int, void*);



// argument를 입력 받게 하자!
// argument 첫번째, 두번째.. 갖고옴
// src = imread(argv[1], 1);
int main(int argc, char** argv)
{
	

	image = imread(argv[1], 1); // Read the file
	if (!image.data)
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Display window", image);
	/// Convert the image to Gray
	cvtColor(image, src_gray, COLOR_BGR2GRAY);


	/// Create a window to display results
	namedWindow(window_name);
	/// Create two Trackbars to choose type of Threshold on one window
	createTrackbar(trackbar_type, window_name, &threshold_type, max_type, Threshold_Demo);
	createTrackbar(trackbar_value, window_name, &threshold_value, max_value, Threshold_Demo);
	/// Call the function to initialize
	Threshold_Demo(0, 0);
	/// Wait until user finishes program
	while (true)
	{
		int c;
		c = waitKey(20);
		if ((char)c == 27)
		{
			break;
		}
	}
}


void Threshold_Demo(int, void*)
{
	/* 0: Binary 1: Binary Inverted 2: Threshold Truncated 3: Threshold to Zero 4: Threshold to Zero Inverted */
	threshold(src_gray, dst, threshold_value, max_BINARY_value, threshold_type);
	imshow(window_name, dst);
}