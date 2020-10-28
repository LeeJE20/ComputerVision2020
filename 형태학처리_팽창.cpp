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

	// 하얀게 물체임
	dilate(dst, dst1, Mat());
	namedWindow("dilated image");
	imshow("dilated image", dst1);

	// 하얀게 물체임. 하얀게 늘어남
	dilate(dst, dst1, Mat(), Point(-1, -1), 5);
	namedWindow("dilated image: 5회 수행");
	imshow("dilated image: 5회 수행", dst1);
	waitKey(0);
	return 0;
}
