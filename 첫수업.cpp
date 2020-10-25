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
	//image = imread(argv[1], 0); // ���
	image = imread(argv[1], 1); // �÷�
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


			// ~~ �÷� �κ�
			// ~ ���� ����
			//result.at<Vec3b>(x, y)[0] = 255 - image.at<Vec3b>(x, y)[0]; // blue
			//result.at<Vec3b>(x, y)[1] = 255 - image.at<Vec3b>(x, y)[1]; // green
			//result.at<Vec3b>(x, y)[2] = 255 - image.at<Vec3b>(x, y)[2]; // red

			// r, g, b �� ���� ū ������ ������
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