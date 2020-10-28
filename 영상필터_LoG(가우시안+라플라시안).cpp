#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include<opencv2/imgproc.hpp>
using namespace cv;
using namespace std;

// LoG


// argument를 입력 받게 하자!
// argument 첫번째, 두번째.. 갖고옴
int main(int argc, char** argv)
{
	Mat src, src_gray, dst;
	int kernel_size = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	const char* window_name = "Laplace Demo";
	const char* window_name1 = "Original Image";
	int c;
	/// Load an image
	/// 
	/// 
	src = imread("test.jpg", 1); // Read the file
	if (!src.data)
	{
		return -1;
	}

	namedWindow(window_name1);
	imshow(window_name1, src);
	// 가우시안 필터로 잡음 제거
	/// Remove noise by blurring with a Gaussian filter
	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);

	/// Convert the image to grayscale
	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	/// Create window
	namedWindow(window_name);

	// 엣지 강조를 위해 라플라시안
	/// Apply Laplace function
	Mat abs_dst;
	Laplacian(src_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
	// 클리핑 용도: 0~255로 제한. 안 하면 쓰레기값 나옴
	convertScaleAbs(dst, abs_dst);
	/// Show what you got
	imshow(window_name, abs_dst);
	waitKey(0);
	return 0;

}
