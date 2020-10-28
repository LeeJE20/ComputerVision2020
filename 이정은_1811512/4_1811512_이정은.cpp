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
	int histSize[1]; // 히스토그램 빈도수
	float hranges[2]; // 히스토그램 최소/최대 화소값
	const float* ranges[1];
	int channels[1]; // 1채널만 사용
public:
	Histogram1D() { // 1차원 히스토그램을 위한 인자 준비
		histSize[0] = 256; // 히스토그램 그림 크기
		hranges[0] = 0.0;
		hranges[1] = 255.0;
		ranges[0] = hranges;
		channels[0] = 0;
	}
	// 1차원 히스토그램 계산
	MatND getHistogram(const Mat& image) {
		MatND hist;
		// 이미지의 히스토그램 계산
		calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges);
		// 인자 값 : 이미지, 단일영상, 대상채널, 마스크 사용안함, 결과히스토그램,
		// 1차원 히스토그램, 빈도수, 화소값 범위
		return hist;
	}


	// 히스토그램을 위한 바 그래프 사용
	Mat getHistogramImage(const Mat& image) {
		MatND hist = getHistogram(image); // 히스토그램 계산
		double maxVal = 0; // 최대 빈도수
		double minVal = 0; // 최소 빈도수
		minMaxLoc(hist, &minVal, &maxVal, 0, 0);
		// 히스토그램을 출력하기 위한 영상
		Mat histImg(histSize[0], histSize[0], CV_8U, Scalar(255));
		// nbins의 90%를 최대점으로 설정
		int hpt = static_cast<int>(0.9 * histSize[0]);
		for (int h = 0; h < histSize[0]; h++) {
			float binVal = hist.at<float>(h);
			int intensity = static_cast<int> (binVal * hpt / maxVal);
			// 두 점간의 거리를 그림
			line(histImg, Point(h, histSize[0]), Point(h, histSize[0] - intensity), Scalar::all(0));
		}
		return histImg;
	}
};









// 드래그로 사각형 그리기

//---전역 변수 선언 ---//
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
//int i = 0; // 클릭됐는지 확인
char imgName[15];

void checkBoundary(); // 드래그가 이미지 벗어났는지 체크
void onMouse(int event, int x, int y, int f, void*); // 마우스 이벤트
void showImage();

void onMouse2(int event, int x, int y, int f, void*); // 마우스 이벤트
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

		Mat image = ROI.clone(); // 경계값으로 이진 영상 생성
		Mat dst;
		// YCbCr로 변환 후 평활화
		//--컬러 영상 평활화 --//
		Mat channels2[3];
		//컬러변환
		cvtColor(image, dst, COLOR_BGR2YCrCb);
		// 개별 채널 분리
		split(dst, channels2);

		Histogram1D h;

		//equalize histogram on the 1st channel (Y)
		equalizeHist(channels2[0], channels2[0]);

		// 평활화 히스토그램
		namedWindow("Equalized ch2", WINDOW_AUTOSIZE); // Create a window for display.
		imshow("Equalized ch2", h.getHistogramImage(channels2[0]));

		//merge 3 channels including the modified 1st channel into one image
		merge(channels2, 3, dst);




		//컬러변환 to BGR
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