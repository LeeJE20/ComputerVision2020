#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include<opencv2/imgproc.hpp>
#include<cmath>
using namespace cv;
using namespace std;

// ������ó�� ����: GrabCut ���� ���


// argument�� �Է� �ް� ����!
// argument ù��°, �ι�°.. �����
int main(int argc, char** argv)
{
	Mat image, gray, binary;
	/// Load image
	image = imread(argv[1], 1); // Read the file
	if (image.empty()) { // Check for invalid input
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	namedWindow("Display window"); // Create a window for display.
	imshow("Display window", image);


	//ROI �κ�
	// define bounding rectangle --����(��ü �κ�) ����
	cv::Rect rectangle2(10, 100, 380, 180);

	cv::Mat bkgModel, fgrModel; // the models (internally used)
	cv::Mat result; // segmentation result (4 possible values)
	cv::Mat foreground(image.size(), CV_8UC3, cv::Scalar(255, 255, 255));


	// GrabCut segmentation
	cv::grabCut(image, // input image
		result, // segmentation result
		rectangle2, bkgModel, fgrModel, 5, cv::GC_INIT_WITH_RECT);


	Mat resultC, resultC2;
	resultC = result.clone();
	threshold(resultC, resultC, 2, 255, THRESH_BINARY);
	imshow("result", resultC);

	// Get the pixels marked as likely foreground
	result = result & 1;
	resultC2 = result.clone();
	threshold(resultC2, resultC2, 0, 255, THRESH_BINARY);
	imshow("result2", resultC2);


	foreground.create(image.size(), CV_8UC3);
	foreground.setTo(cv::Scalar(255, 255, 255));
	image.copyTo(foreground, result); // bg pixels not copied

	// draw rectangle on original image
	cv::rectangle(image, rectangle2, cv::Scalar(255, 255, 255), 1);
	cv::namedWindow("Image 2");
	cv::imshow("Image 2", image);
	// display result
	cv::namedWindow("Foreground objects");
	cv::imshow("Foreground objects", foreground);
	waitKey(0);
	return 0;
}