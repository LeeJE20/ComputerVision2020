#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
using namespace cv;
using namespace std;

// argument�� �Է� �ް� ����!
int main(int argc, char** argv)
{
	// �̹�������
	Mat image;

	//�ε�
	// �����̸����� �ε�
	// 0�̸� ���
	image = imread(argv[1], 0);

	//�����ֱ�
	// ������ �̸�
	namedWindow("original");

	waitKey();

	return 0;
}