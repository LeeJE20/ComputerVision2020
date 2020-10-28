#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include<opencv2/imgproc.hpp>
using namespace cv;
using namespace std;

// argument�� �Է� �ް� ����!
// argument ù��°, �ι�°.. �����
int main(int argc, char** argv)
{
	// �̹�������
	// result: ��ȭ ��. ī���صδ°� ����. �÷��� �÷���, ����̸� ������� ī�ǰ� �ȴ�.
	Mat image, result;


	// �ε�
	// �̹����� ���Ͽ��� �о����
	// �����̸����� �ε�
	// 0�̸� ���, 1�̸� �÷�
	// �� �ָ� �ڵ� ����
	//image = imread(argv[1], 0); // ���
	image = imread(argv[1], 1); // �÷�

	cvtColor(image, result, COLOR_BGR2YCrCb);

	//�����ֱ�
	// ������ �̸�
	namedWindow("original");

	// �������� �����쿡 image ���ۿ� �ִ°� �׸���
	// ����: ����� �����͸� �޸𸮿� �ִ� ���� �ϱ� ���� �ӽ� �޸�
	imshow("original", image);






	namedWindow("YCrCb Image");
	imshow("YCrCb Image", result);
	waitKey();

	return 0;
}