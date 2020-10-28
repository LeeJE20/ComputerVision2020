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
const int alpha_slider_max = 100;

double alpha;
double beta;
Mat image1, image2, dst;




int main(int argc, char** argv)
{

	cout << "press 'm' or 'esc'" << endl;
	image1 = imread(argv[1], 1);
	image2 = imread(argv[2], 1);
	namedWindow("Display Blend");

	imshow("Display Blend", image1);
	int k;
	k = waitKey(0);
	while (k != 'm' && k != 27)
	{
		cout << "press 'm' or 'esc'" << endl;
		k = waitKey(0);
	}
	if (k == 27) return 0;
	cout << "start!" << endl;
	if (k == 'm')
	{
		for (int i = 0; i <= 100; i++)
		{
			// ���Ĵ� 0~1���� ���� �ȴ�
			alpha = (double)i / alpha_slider_max;
			beta = (1.0 - alpha);
			// �� ���� ����
			addWeighted(image2, alpha, image1, beta, 0.0, dst);

			imshow("Display Blend", dst);

			if (waitKey(1) > 0) continue;


		}
	}

	cout << "finished" << endl << "press 'esc'" << endl;
	k = waitKey(0);
	while (k != 27)
	{
		cout << "press 'esc'" << endl;
		k = waitKey(0);
	}
	cout << "bye" << endl;
	return 0;
}
