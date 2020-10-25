#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include<opencv2/imgproc.hpp>
using namespace cv;
using namespace std;

// 이미지 사이즈 조정


// argument를 입력 받게 하자!
// argument 첫번째, 두번째.. 갖고옴
int main(int argc, char** argv)
{
	Mat src, dst, tmp;
	char window_name[] = "Pyramids Demo";




	/// General instructions
	printf("\n Zoom In-Out demo \n ");
	printf("------------------ \n");
	printf(" * [u] -> Zoom in \n");
	printf(" * [d] -> Zoom out \n");
	printf(" * [ESC] -> Close program \n \n");
	/// Test image - Make sure it s divisible by 2^{n}
	src = imread(argv[1], 1); // Read the file
	if (!src.data)
	{
		printf(" No data! -- Exiting the program \n");
		return -1;
	}
	tmp = src;
	dst = tmp;

	/// Create window
	namedWindow("Original Image", WINDOW_AUTOSIZE);
	imshow("Original Image", src);
	/// Loop
	while (true) {
		int c;
		c = waitKey(10);
		if ((char)c == 27) { printf("program finished!\n"); break; } // ESC 키 입력 시 종료
		if ((char)c == 'u')
		{
			pyrUp(tmp, dst, Size(tmp.cols * 2, tmp.rows * 2));
			printf("** Zoom In: Image x 2 \n");
		}
		else if ((char)c == 'd') {
			pyrDown(tmp, dst, Size(tmp.cols / 2, tmp.rows / 2));
			printf("** Zoom Out: Image / 2 \n");
		}
		imshow(window_name, dst);
		tmp = dst;
	}
	return 0;

}
