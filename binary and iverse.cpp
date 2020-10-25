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
	// result: ��ȭ ��. ī���صδ°� ����. �÷��� �÷���, ����̸� ������� ī�ǰ� �ȴ�.
	Mat image, result;

	int th = 128; // ����ȭ ��谪

	// �ε�
	// �̹����� ���Ͽ��� �о����
	// �����̸����� �ε�
	// 0�̸� ���, 1�̸� �÷�
	// �� �ָ� �ڵ� ����
	image = imread(argv[1], 0); // ���
	//image = imread(argv[1], 1); // �÷�
	result = image.clone();

	//�����ֱ�
	// ������ �̸�
	namedWindow("original");

	// �������� �����쿡 image ���ۿ� �ִ°� �׸���
	// ����: ����� �����͸� �޸𸮿� �ִ� ���� �ϱ� ���� �ӽ� �޸�
	imshow("original", image);




	//processing algorithms
	for (int x = 0; x < image.rows; x++)
	{
		for (int y = 0; y < image.cols; y++)
		{
			// ~~ ��� �κ� 


			// ~���� ���� �����
			//result.at<uchar>(x, y) = 255 - image.at<uchar>(x, y);

			// ~����ȭ
			//x, y ��ġ�� �ȼ� �� 8��Ʈ�� �������
			int value = image.at<uchar>(x, y);

			if (value > th)
			{
				result.at<uchar>(x, y) = 255;
			}
			else
			{
				result.at<uchar>(x, y) = 0;
			}


			// ~~ �÷� �κ�
			// ~ ���� ����
			//result.at<Vec3b>(x, y)[0] = 255 - image.at<Vec3b>(x, y)[0]; // blue
			//result.at<Vec3b>(x, y)[1] = 255 - image.at<Vec3b>(x, y)[1]; // green
			//result.at<Vec3b>(x, y)[2] = 255 - image.at<Vec3b>(x, y)[2]; // red
		}
	}

	//namedWindow("Inverse Image");
	//imshow("Inverse Image", result);

	namedWindow("Binary Image");
	imshow("Binary Image", result);
	waitKey();

	return 0;
}