#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include<opencv2/imgproc.hpp>
using namespace cv;
using namespace std;

// 팽창


///--- Global variables----///
int threshold_value = 0;
int threshold_type = 3;
int const max_BINARY_value = 255;
Mat image, src_gray, dst, dst1;
const char* window_name = "original";





// argument를 입력 받게 하자!
// argument 첫번째, 두번째.. 갖고옴
// src = imread(argv[1], 1);
int main(int argc, char** argv)
{


	image = imread("test.jpg", 0); // Read the file
	if (!image.data)
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	namedWindow("Display window"); // Create a window for display.
	imshow("Display window", image);
	/// Convert the image to Gray
	//cvtColor(image, src_gray, COLOR_BGR2GRAY);
	/// Create a window to display results
	namedWindow(window_name);
	imshow(window_name, image);



	threshold(image, image, threshold_value = 120, max_BINARY_value, 1);
	namedWindow("Binary image");
	imshow("Binary image", image);
	Mat skel(image.size(), CV_8UC1, cv::Scalar(0));
	Mat temp(image.size(), CV_8UC1);
	cv::Mat element = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));
	bool done;
	do {
		cv::morphologyEx(image, temp, cv::MORPH_OPEN, element);
		cv::bitwise_not(temp, temp);
		cv::bitwise_and(image, temp, temp);
		cv::bitwise_or(skel, temp, skel);
		cv::erode(image, image, element);
		double max;
		cv::minMaxLoc(image, 0, &max);
		done = (max == 0);
	} while (!done);

	imshow("Skeleton", skel);
	waitKey(0);
	return 0;
}