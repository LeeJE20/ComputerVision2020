#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
using namespace cv;
using namespace std;

// argument를 입력 받게 하자!
int main(int argc, char** argv)
{
	// 이미지버퍼
	Mat image;

	//로딩
	// 파일이름으로 로드
	// 0이면 흑백
	image = imread(argv[1], 0);

	//보여주기
	// 윈도우 이름
	namedWindow("original");

	waitKey();

	return 0;
}