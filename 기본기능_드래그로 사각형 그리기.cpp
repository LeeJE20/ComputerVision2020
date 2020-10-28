#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include<opencv2/imgproc.hpp>
using namespace cv;
using namespace std;

// 드래그로 사각형 그리기

//---전역 변수 선언 ---//
Mat src, img, ROI;
Rect cropRect(0, 0, 0, 0);
Point P1(0, 0);
Point P2(0, 0);

const char* winName = "Crop Image";
bool clicked = false;
int i = 0; // 클릭됐는지 확인
char imgName[15];

void checkBoundary(); // 드래그가 이미지 벗어났는지 체크
void onMouse(int event, int x, int y, int f, void*); // 마우스 이벤트
void showImage();

void myFunction();


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

	src = imread("test.jpg", 1);
	namedWindow(winName, WINDOW_AUTOSIZE);
	setMouseCallback(winName, onMouse, NULL);
	imshow(winName, src);
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
	} // end of “while()”
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

		Mat thresholdedImage = ROI.clone(); // 경계값으로 이진 영상 생성

		cvtColor(thresholdedImage, thresholdedImage, COLOR_BGR2GRAY);
		// 원본, 결과, 경계값, max값, 옵션
		threshold(thresholdedImage, thresholdedImage, 60, 255, THRESH_BINARY);

		imshow("myfunction", thresholdedImage);
	}

}