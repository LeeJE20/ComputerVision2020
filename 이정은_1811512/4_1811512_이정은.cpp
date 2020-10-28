#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include<opencv2/imgproc.hpp>
using namespace cv;
using namespace std;



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









// �巡�׷� �簢�� �׸���

//---���� ���� ���� ---//
Mat src, img, ROI, gray, lgray, ROIg;
Rect cropRect(0, 0, 0, 0);
Point P1(0, 0);
Point P2(0, 0);

Rect cropRectg(0, 0, 0, 0);
Point P1g(0, 0);
Point P2g(0, 0);



const char* winName = "Color Image";
const char* grayWin = "Gray Image";
bool clicked = false;
bool clickedg = false;
//int i = 0; // Ŭ���ƴ��� Ȯ��
char imgName[15];

void checkBoundary(); // �巡�װ� �̹��� ������� üũ
void onMouse(int event, int x, int y, int f, void*); // ���콺 �̺�Ʈ
void showImage();

void onMouse2(int event, int x, int y, int f, void*); // ���콺 �̺�Ʈ
void showImage2();

void myFunction();
void checkBoundary2();

int main(int argc, char** argv)
{
	cout << "Click and drag for Selection" << endl << endl;
	cout << "------> Press 's' to save" << endl << endl;
	cout << "------> Press '8' to move up" << endl;
	cout << "------> Press '2' to move down" << endl;
	cout << "------> Press '6' to move right" << endl;
	cout << "------> Press '4' to move left" << endl << endl;
	cout << "------> Press 'w' increas top" << endl;
	cout << "------> Press 'x' increas bottom" << endl;
	cout << "------> Press 'd' increas right" << endl;
	cout << "------> Press 'a' increas left" << endl << endl;
	cout << "------> Press 't' decrease top" << endl;
	cout << "------> Press 'b' decrease bottom" << endl;
	cout << "------> Press 'h' decrease right" << endl;
	cout << "------> Press 'f' decrease left" << endl << endl;
	cout << "------> Press 'r' to reset" << endl;
	cout << "------> Press 'Esc' to quit" << endl << endl;

	src = imread(argv[1], 1);



	namedWindow(winName, WINDOW_AUTOSIZE);
	setMouseCallback(winName, onMouse, NULL);


	imshow(winName, src);



	cvtColor(src, gray, COLOR_BGR2GRAY);
	namedWindow(grayWin, WINDOW_AUTOSIZE);
	setMouseCallback(grayWin, onMouse2, NULL);
	imshow(grayWin, gray);


	while (1) {
		char c = waitKey();
		if (c == 's' && !ROI.empty()) {
			//sprintf(imgName,"%d.jpg",i++);
			imwrite("croppedImg.jpg", ROI);
			cout << " Saved " << imgName << endl;
		}
		if (c == '6') cropRect.x++;
		if (c == '4') cropRect.x--;
		if (c == '8') cropRect.y--;
		if (c == '2') cropRect.y++;
		if (c == 'w') { cropRect.y--; cropRect.height++; }
		if (c == 'd') cropRect.width++;
		if (c == 'x') cropRect.height++;
		if (c == 'a') { cropRect.x--; cropRect.width++; }


		if (c == 't') { cropRect.y++; cropRect.height--; }
		if (c == 'h') cropRect.width--;
		if (c == 'b') cropRect.height--;
		if (c == 'f') { cropRect.x++; cropRect.width--; }
		if (c == 27) break;
		if (c == 'r') {
			cropRect.x = 0; cropRect.y = 0;
			cropRect.width = 0; cropRect.height = 0;
		}
		showImage();
		showImage2();
	} // end of ��while()��
	return 0;
}




void onMouse(int event, int x, int y, int f, void*) {
	switch (event) {
	case EVENT_LBUTTONDOWN:
		clicked = true;
		P1.x = x;
		P1.y = y;
		P2.x = x;
		P2.y = y;
		break;
	case EVENT_LBUTTONUP:
		P2.x = x;
		P2.y = y;
		clicked = false;
		break;
	case EVENT_MOUSEMOVE:
		if (clicked) {
			P2.x = x;
			P2.y = y;
		}
		break;
	default: break;
	}



	if (clicked) {
		if (P1.x > P2.x) {
			cropRect.x = P2.x;
			cropRect.width = P1.x - P2.x;
		}
		else {
			cropRect.x = P1.x;
			cropRect.width = P2.x - P1.x;
		}
		if (P1.y > P2.y) {
			cropRect.y = P2.y;
			cropRect.height = P1.y - P2.y;
		}
		else {
			cropRect.y = P1.y;
			cropRect.height = P2.y - P1.y;
		}
	}
	showImage();

}



void checkBoundary() {
	//check croping rectangle exceed image boundary
	if (cropRect.width > img.cols - cropRect.x)
		cropRect.width = img.cols - cropRect.x;
	if (cropRect.height > img.rows - cropRect.y)
		cropRect.height = img.rows - cropRect.y;
	if (cropRect.x < 0)
		cropRect.x = 0;
	if (cropRect.y < 0)
		cropRect.height = 0;
}


void showImage() {
	img = src.clone();
	checkBoundary();
	if (cropRect.width > 0 && cropRect.height > 0) {
		ROI = src(cropRect);
		imshow("cropped", ROI);
	}
	rectangle(img, cropRect, Scalar(0, 255, 0), 1, 8, 0);
	imshow(winName, img);

	myFunction();
}


void myFunction()
{
	if (cropRect.width > 0 && cropRect.height > 0) {

		Mat image = ROI.clone(); // ��谪���� ���� ���� ����
		Mat dst;
		// YCbCr�� ��ȯ �� ��Ȱȭ
		//--�÷� ���� ��Ȱȭ --//
		Mat channels2[3];
		//�÷���ȯ
		cvtColor(image, dst, COLOR_BGR2YCrCb);
		// ���� ä�� �и�
		split(dst, channels2);

		Histogram1D h;

		//equalize histogram on the 1st channel (Y)
		equalizeHist(channels2[0], channels2[0]);

		// ��Ȱȭ ������׷�
		namedWindow("Equalized ch2", WINDOW_AUTOSIZE); // Create a window for display.
		imshow("Equalized ch2", h.getHistogramImage(channels2[0]));

		//merge 3 channels including the modified 1st channel into one image
		merge(channels2, 3, dst);




		//�÷���ȯ to BGR
		cvtColor(dst, dst, COLOR_YCrCb2BGR);
		namedWindow("Equalized Image by YCrCb", WINDOW_AUTOSIZE); // Create a window for display.
		imshow("Equalized Image by YCrCb", dst);

		/*imshow("myfunction", thresholdedImage);*/
	}

}









void onMouse2(int event, int x, int y, int f, void*) {
	switch (event) {
	case EVENT_LBUTTONDOWN:
		clickedg = true;
		P1g.x = x;
		P1g.y = y;
		P2g.x = x;
		P2g.y = y;
		break;
	case EVENT_LBUTTONUP:
		P2g.x = x;
		P2g.y = y;
		clickedg = false;
		break;
	case EVENT_MOUSEMOVE:
		if (clickedg) {
			P2g.x = x;
			P2g.y = y;
		}
		break;
	default: break;
	}



	if (clickedg) {
		if (P1g.x > P2g.x) {
			cropRectg.x = P2g.x;
			cropRectg.width = P1g.x - P2g.x;
		}
		else {
			cropRectg.x = P1g.x;
			cropRectg.width = P2g.x - P1g.x;
		}
		if (P1g.y > P2g.y) {
			cropRectg.y = P2g.y;
			cropRectg.height = P1g.y - P2g.y;
		}
		else {
			cropRectg.y = P1g.y;
			cropRectg.height = P2g.y - P1g.y;
		}
	}
	showImage2();

}



void checkBoundary2() {
	//check croping rectangle exceed image boundary
	if (cropRectg.width > img.cols - cropRectg.x)
		cropRectg.width = img.cols - cropRectg.x;
	if (cropRectg.height > img.rows - cropRectg.y)
		cropRectg.height = img.rows - cropRectg.y;
	if (cropRectg.x < 0)
		cropRectg.x = 0;
	if (cropRectg.y < 0)
		cropRectg.height = 0;
}

void showImage2() {

	lgray = gray.clone();
	checkBoundary();
	if (cropRectg.width > 0 && cropRectg.height > 0) {
		ROIg = gray(cropRectg);
		imshow("croppedGray", ROIg);
	}
	rectangle(lgray, cropRectg, Scalar(0, 255, 0), 1, 8, 0);
	imshow(grayWin, lgray);


}