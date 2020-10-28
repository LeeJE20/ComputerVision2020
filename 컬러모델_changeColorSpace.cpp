#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include<opencv2/imgproc.hpp>
using namespace cv;
using namespace std;

// argument를 입력 받게 하자!
// argument 첫번째, 두번째.. 갖고옴
int main(int argc, char** argv)
{
	// 이미지버퍼
	// result: 변화 후. 카피해두는게 좋다. 컬러면 컬러로, 흑백이면 흑백으로 카피가 된다.
	Mat image, result;


	// 로딩
	// 이미지를 파일에서 읽어들임
	// 파일이름으로 로드
	// 0이면 흑백, 1이면 컬러
	// 안 주면 자동 설정
	//image = imread(argv[1], 0); // 흑백
	image = imread(argv[1], 1); // 컬러

	cvtColor(image, result, COLOR_BGR2YCrCb);

	//보여주기
	// 윈도우 이름
	namedWindow("original");

	// 오리지널 윈도우에 image 버퍼에 있는걸 그리기
	// 버퍼: 사용자 데이터를 메모리에 넣다 뺐다 하기 위한 임시 메모리
	imshow("original", image);






	namedWindow("YCrCb Image");
	imshow("YCrCb Image", result);
	waitKey();

	return 0;
}