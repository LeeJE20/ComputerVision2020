#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include<opencv2/imgproc.hpp>
using namespace cv;
using namespace std;

// 영상 위에 임의의 text 표시해주기

int main(int argc, char** argv)
{
	string text = "Funny text inside the box";
	int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
	double fontScale = 2;
	int thickness = 3;
	Mat img(600, 800, CV_8UC3, Scalar::all(0));
	int baseline = 0;
	Size textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
	baseline += thickness;
	// center the text
	Point textOrg((img.cols - textSize.width) / 2, (img.rows + textSize.height) / 2);
	// draw the box
	rectangle(img, textOrg + Point(0, baseline), textOrg + Point(textSize.width, -textSize.height), Scalar(0, 0, 255));
	// ... and the baseline first
	line(img, textOrg + Point(0, thickness), textOrg + Point(textSize.width, thickness), Scalar(0, 0, 255));
	// then put the text itself
	putText(img, text, textOrg, fontFace, fontScale, Scalar::all(255), thickness, 8);
	namedWindow("Display text");
	imshow("Display text", img);
	waitKey(0);// Wait for a keystroke in the window

	return 0;
}