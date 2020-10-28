#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include<opencv2/imgproc.hpp>
using namespace cv;
using namespace std;

#pragma warning(disable : 4996)

// ���� ���� ������ text ǥ�����ֱ�

// Global Variables
const int alpha_slider_max = 255;
int alpha_slider;
double alpha;
double beta;
Mat image1, image2, dst;
void on_trackbar(int, void*);



int main(int argc, char** argv)
{
	image1 = imread(argv[1], 0);

	namedWindow("Display Blend");



	/// Create Trackbars
	char TrackbarName[50];
	sprintf(TrackbarName, "Alpha x %d", alpha_slider_max);
	// Ʈ���� �̸�, ������, Ʈ���� ��, Ʈ���� �ִ밪, ��Ʈ���� �Լ��� ��� ����
	createTrackbar(TrackbarName, "Display Blend", &alpha_slider, alpha_slider_max, on_trackbar);
	/// Show some stuff
	// ���� �����̴� �ʱⰪ 0
	on_trackbar(alpha_slider, 0);



	waitKey(0);// Wait for a keystroke in the window
	destroyWindow("Display Blend");// �Ǵ� destroyWindowall();
	return 0;
}


/**
* @function on_trackbar
* @brief Callback for trackbar
*/
void on_trackbar(int, void*)
{
	// ���� �����̴� ������ ����ȭ
	threshold(image1, dst, alpha_slider, 255, 0);




	string text = "Threshold = " + to_string(alpha_slider);
	int fontFace = FONT_HERSHEY_PLAIN;
	double fontScale = 2;
	int thickness = 3;

	int baseline = 0;
	Size textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
	baseline += thickness;
	// center the text
	Point textOrg((image1.cols - textSize.width) / 2, (image1.rows + textSize.height) / 1.2);


	// then put the text itself
	putText(dst, text, textOrg, fontFace, fontScale, Scalar(130, 130, 130), thickness, 8);
	//namedWindow("Display text");
	//imshow("Display text", dst);



	imshow("Display Blend", dst);
}