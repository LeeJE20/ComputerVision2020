#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include<opencv2/imgproc.hpp>
using namespace cv;
using namespace std;
// ~~������׷� ��Ȱȭ


class Histogram1D {
private:
	int histSize[1]; // ������׷� �󵵼�
	float hranges[2]; // ������׷� �ּ�/�ִ� ȭ�Ұ�
	const float* ranges[1];
	int channels[1]; // 1ä�θ� ���
public:
	Histogram1D() { // 1���� ������׷��� ���� ���� �غ�
		histSize[0] = 256; // ������׷� �׸� ũ��
		hranges[0] = 0.0;
		hranges[1] = 255.0;
		ranges[0] = hranges;
		channels[0] = 0;
	}
	// 1���� ������׷� ���
	MatND getHistogram(const Mat& image) {
		MatND hist;
		// �̹����� ������׷� ���
		calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges);
		// ���� �� : �̹���, ���Ͽ���, ���ä��, ����ũ ������, ���������׷�,
		// 1���� ������׷�, �󵵼�, ȭ�Ұ� ����
		return hist;
	}


	// ������׷��� ���� �� �׷��� ���
	Mat getHistogramImage(const Mat& image) {
		MatND hist = getHistogram(image); // ������׷� ���
		double maxVal = 0; // �ִ� �󵵼�
		double minVal = 0; // �ּ� �󵵼�
		minMaxLoc(hist, &minVal, &maxVal, 0, 0);
		// ������׷��� ����ϱ� ���� ����
		Mat histImg(histSize[0], histSize[0], CV_8U, Scalar(255));
		// nbins�� 90%�� �ִ������� ����
		int hpt = static_cast<int>(0.9 * histSize[0]);
		for (int h = 0; h < histSize[0]; h++) {
			float binVal = hist.at<float>(h);
			int intensity = static_cast<int> (binVal * hpt / maxVal);
			// �� ������ �Ÿ��� �׸�
			line(histImg, Point(h, histSize[0]), Point(h, histSize[0] - intensity), Scalar::all(0));
		}
		return histImg;
	}
};



// argument�� �Է� �ް� ����!
// argument ù��°, �ι�°.. �����
int main(int argc, char** argv)
{
	Mat image, dst, result1, result2;
	/// Load image
	image = imread("test.jpg", 1); // Read the file
	if (image.empty()) { // Check for invalid input
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	namedWindow("Display window", WINDOW_AUTOSIZE);
	imshow("Display window", image);


	Histogram1D h;

	// BGR ��� ���� ��Ȱȭ
	//--�÷� ���� ��Ȱȭ --//
	Mat channels[3];
	// ���� ä�� �и�
	split(image, channels);

	equalizeHist(channels[0], channels[0]);
	equalizeHist(channels[1], channels[1]);
	equalizeHist(channels[2], channels[2]);
	//merge 3 channels including the modified 1st channel into one image
	merge(channels, 3, result1);
	namedWindow("Equalized Image by BGR", WINDOW_AUTOSIZE);
	// Create a window for display.
	imshow("Equalized Image by BGR", result1);



	// YCbCr�� ��ȯ �� ��Ȱȭ
	//--�÷� ���� ��Ȱȭ --//
	Mat channels2[3];
	//�÷���ȯ
	cvtColor(image, dst, COLOR_BGR2YCrCb);
	// ���� ä�� �и�
	split(dst, channels2);

	// ���� ������׷�
	namedWindow("Y Histogram", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Y Histogram", h.getHistogramImage(channels2[0]));


	//equalize histogram on the 1st channel (Y)
	equalizeHist(channels2[0], channels2[0]);

	// ��Ȱȭ ������׷�
	namedWindow("Equalized ch2", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Equalized ch2", h.getHistogramImage(channels2[0]));

	//merge 3 channels including the modified 1st channel into one image
	merge(channels2, 3, dst);

	// ��Ȱȭ ������׷�
	namedWindow("Equalized Histogram", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Equalized Histogram", h.getHistogramImage(dst));


	//�÷���ȯ to BGR
	cvtColor(dst, result2, COLOR_YCrCb2BGR);
	namedWindow("Equalized Image by YCrCb", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Equalized Image by YCrCb", result2);








	waitKey(0);
	return 0;

}


