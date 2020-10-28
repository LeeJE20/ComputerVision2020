#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include<opencv2/imgproc.hpp>
using namespace cv;
using namespace std;

// ��â


///--- Global variables----///
int threshold_value = 0;
int threshold_type = 3;
int const max_BINARY_value = 255;
Mat image, src_gray, dst, dst1;
const char* window_name = "original";





// argument�� �Է� �ް� ����!
// argument ù��°, �ι�°.. �����
// src = imread(argv[1], 1);
int main(int argc, char** argv)
{


	image = imread("test.jpg", 1); // Read the file
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
	imshow(window_name, src_gray);



	threshold(src_gray, dst, threshold_value = 120, max_BINARY_value, threshold_type);

	namedWindow("Binary image");
	imshow("Binary image", dst);

	// Open the image
	cv::Mat element3(3, 3, CV_8U, cv::Scalar(1));
	cv::Mat opened;
	cv::morphologyEx(image, opened, cv::MORPH_OPEN, element3);
	// Display the opened image
	cv::namedWindow("Opened Image");
	cv::imshow("Opened Image", opened);



	// Close the image
	cv::Mat element5(5, 5, CV_8U, cv::Scalar(1));
	cv::Mat closed;
	cv::morphologyEx(image, closed, cv::MORPH_CLOSE, element5);
	// Display the opened image
	cv::namedWindow("Closed Image");
	cv::imshow("Closed Image", closed);

	waitKey(0);
	return 0;
}
