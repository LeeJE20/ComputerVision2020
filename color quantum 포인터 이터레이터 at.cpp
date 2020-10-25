#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include<opencv2/imgproc.hpp>
using namespace cv;
using namespace std;
// ~~ȭ����ó�� �ǽ�


void colorReduce_pointer(Mat& image, int div);
void colorReduce_iter(Mat& image, int div);
void colorReduce_at(Mat& image, int div);


// argument�� �Է� �ް� ����!
// argument ù��°, �ι�°.. �����
int main(int argc, char** argv)
{
	cout << fixed;
	cout.precision(15);

	Mat image, result_pointer, result_iter, result_at;
	double t_pointer, t_iter, t_at;
	//Read the file
	image = imread("test.jpg", IMREAD_COLOR);


	// Check for invalid input
	if (image.empty())
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	// Create a window for display
	namedWindow("original", WINDOW_AUTOSIZE);

	// Show our image inside it
	imshow("original", image);

	result_pointer = image.clone();
	result_iter = image.clone();
	result_at = image.clone();





	// ~~ ������ ���
	t_pointer = (double)getTickCount();
	colorReduce_pointer(result_pointer, 64);
	t_pointer = ((double)getTickCount() - t_pointer) / getTickFrequency();
	namedWindow("pointer", WINDOW_AUTOSIZE);
	imshow("pointer", result_pointer);
	cout << "T_pointer(ms) = " << t_pointer << endl << endl;

	// ~~ ���ͷ����� ���
	t_iter = (double)getTickCount();
	colorReduce_iter(result_iter, 64);
	t_iter = ((double)getTickCount() - t_iter) / getTickFrequency();
	namedWindow("iter", WINDOW_AUTOSIZE);
	imshow("iter", result_iter);
	cout << "T_iter(ms)    = " << t_iter << endl << endl;

	// ~~ at()�Լ� ���
	t_at = (double)getTickCount();
	colorReduce_at(result_at, 64);
	t_at = ((double)getTickCount() - t_at) / getTickFrequency();
	namedWindow("at", WINDOW_AUTOSIZE);
	imshow("at", result_at);
	cout << "T_at(ms)      = " << t_at << endl << endl;

	waitKey(0);

	return 0;
}


void colorReduce_pointer(Mat& image, int div)
{
	double t = (double)getTickCount();
	int nl = image.rows; // �� ����
	int nc = image.cols * image.channels(); // �� ���� ������ ����
	t = ((double)getTickCount() - t) / getTickFrequency();
	cout << "T_pointer_�ʱ�ȭ(ms) = " << t << endl;

	uchar* data1 = image.ptr<uchar>(0);
	cout << "(int)*data1 = " << (int)*data1 << endl;
	cout << "data1[1] = " << (int)data1[1] << endl;


	double t1 = (double)getTickCount();
	for (int j = 0; j < nl; j++)
	{
		//j���� �ּ�(nc����ŭ) ��������
		uchar* data = image.ptr<uchar>(j);
		for (int i = 0; i < nc; i++)
		{
			//�� ȭ�Ұ� ����
			data[i] = data[i] / div * div + div / 2;
		}

	}
	t1 = ((double)getTickCount() - t1) / getTickFrequency();
	cout << "T_pointer_����(ms) = " << t1 << endl;
}



void colorReduce_iter(Mat& image, int div)
{
	double t = (double)getTickCount();
	Mat_<Vec3b>::iterator it = image.begin<Vec3b>();
	Mat_<Vec3b>::iterator itend = image.end<Vec3b>();
	t = ((double)getTickCount() - t) / getTickFrequency();
	cout << "T_iter_�ʱ�ȭ(ms) = " << t << endl;


	cout << "(*it) = " << (*it) << endl;
	cout << "(*it)[0] = " << (int)((*it)[0]) << endl;

	//��� ȭ�� ��ȸ
	double t1 = (double)getTickCount();
	for (; it != itend; ++it)
	{
		//����ȭ��ó��
		(*it)[0] = (*it)[0] / div * div + div / 2; //b
		(*it)[1] = (*it)[1] / div * div + div / 2; //g
		(*it)[2] = (*it)[2] / div * div + div / 2; //r
	}
	t1 = ((double)getTickCount() - t1) / getTickFrequency();
	cout << "T_iter_����(ms) = " << t1 << endl;
}



void colorReduce_at(Mat& image, int div)
{
	double t = (double)getTickCount();
	int nl = image.rows; // �� ����
	int nc = image.cols; // �� ����
	t = ((double)getTickCount() - t) / getTickFrequency();
	cout << "T_at_�ʱ�ȭ(ms) = " << t << endl;

	cout << "image.at<Vec3b>(0, 0) = " << image.at<Vec3b>(0, 0) << endl;
	cout << "image.at<Vec3b>(0, 0)[0] = " << (int)image.at<Vec3b>(0, 0)[0] << endl;

	// ��� ȭ�� ��ȸ
	double t1 = (double)getTickCount();
	for (int j = 0; j < nl; j++)
	{
		for (int i = 0; i < nc; i++)
		{
			//�� ȭ�� ó��
			image.at<Vec3b>(j, i)[0] = image.at<Vec3b>(j, i)[0] / div * div + div / 2; //b
			image.at<Vec3b>(j, i)[1] = image.at<Vec3b>(j, i)[1] / div * div + div / 2; //g
			image.at<Vec3b>(j, i)[2] = image.at<Vec3b>(j, i)[2] / div * div + div / 2; //r
		}
	}

	t1 = ((double)getTickCount() - t1) / getTickFrequency();
	cout << "T_at_����(ms) = " << t1 << endl;
}