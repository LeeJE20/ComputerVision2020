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
	// result: 변화 후. 카피해두는게 좋다. 컬러면 컬러로, 흑백이면 흑백으로 카피가 된다.
	Mat image, result;

	int th = 128; // 이진화 경계값

	// 로딩
	// 이미지를 파일에서 읽어들임
	// 파일이름으로 로드
	// 0이면 흑백, 1이면 컬러
	// 안 주면 자동 설정
	//image = imread(argv[1], 0); // 흑백
	image = imread(argv[1], 1); // 컬러
	result = image.clone();

	//보여주기
	// 윈도우 이름
	namedWindow("original");

	// 오리지널 윈도우에 image 버퍼에 있는걸 그리기
	// 버퍼: 사용자 데이터를 메모리에 넣다 뺐다 하기 위한 임시 메모리
	imshow("original", image);




	//processing algorithms
	for (int x = 0; x < image.rows; x++)
	{
		for (int y = 0; y < image.cols; y++)
		{
			// ~~ 흑백 부분 


			// ~반전 영상 만들기
			//result.at<uchar>(x, y) = 255 - image.at<uchar>(x, y);

			// ~이진화
			//x, y 위치의 픽셀 값 8비트로 갖고오기
			//int value = image.at<uchar>(x, y);
			//
			//if (value > th)
			//{
			//	result.at<uchar>(x, y) = 255;
			//}
			//else
			//{
			//	result.at<uchar>(x, y) = 0;
			//}


			// ~~ 컬러 부분
			// ~ 반전 영상
			//result.at<Vec3b>(x, y)[0] = 255 - image.at<Vec3b>(x, y)[0]; // blue
			//result.at<Vec3b>(x, y)[1] = 255 - image.at<Vec3b>(x, y)[1]; // green
			//result.at<Vec3b>(x, y)[2] = 255 - image.at<Vec3b>(x, y)[2]; // red

			// r, g, b 중 제일 큰 값으로 돌리기
			int b = image.at<Vec3b>(x, y)[0]; // blue
			int g = image.at<Vec3b>(x, y)[1]; // green
			int r = image.at<Vec3b>(x, y)[2]; // red

			if (b >= r && b >= g)
			{
				result.at<Vec3b>(x, y)[0] = 255;
				result.at<Vec3b>(x, y)[1] = 0;
				result.at<Vec3b>(x, y)[2] = 0;
			}
			else if (g >= b && g >= r)
			{
				result.at<Vec3b>(x, y)[0] = 0;
				result.at<Vec3b>(x, y)[1] = 255;
				result.at<Vec3b>(x, y)[2] = 0;
			}
			else if (r >= b && r >= g)
			{
				result.at<Vec3b>(x, y)[0] = 0;
				result.at<Vec3b>(x, y)[1] = 0;
				result.at<Vec3b>(x, y)[2] = 255;
			}
		}
	}

	//namedWindow("Inverse Image");
	//imshow("Inverse Image", result);

	//namedWindow("Binary Image");
	//imshow("Binary Image", result);

	namedWindow("rgb max Image");
	imshow("rgb max Image", result);
	waitKey();

	return 0;
}