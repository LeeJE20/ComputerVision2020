#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include<opencv2/imgproc.hpp>
using namespace cv;
using namespace std;
// ~~히스토그램 평활화


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



// argument를 입력 받게 하자!
// argument 첫번째, 두번째.. 갖고옴
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

	// BGR 밴드 각각 평활화
	//--컬러 영상 평활화 --//
	Mat channels[3];
	// 개별 채널 분리
	split(image, channels);

	equalizeHist(channels[0], channels[0]);
	equalizeHist(channels[1], channels[1]);
	equalizeHist(channels[2], channels[2]);
	//merge 3 channels including the modified 1st channel into one image
	merge(channels, 3, result1);
	namedWindow("Equalized Image by BGR", WINDOW_AUTOSIZE);
	// Create a window for display.
	imshow("Equalized Image by BGR", result1);



	// YCbCr로 변환 후 평활화
	//--컬러 영상 평활화 --//
	Mat channels2[3];
	//컬러변환
	cvtColor(image, dst, COLOR_BGR2YCrCb);
	// 개별 채널 분리
	split(dst, channels2);

	// 원본 히스토그램
	namedWindow("Y Histogram", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Y Histogram", h.getHistogramImage(channels2[0]));


	//equalize histogram on the 1st channel (Y)
	equalizeHist(channels2[0], channels2[0]);

	// 평활화 히스토그램
	namedWindow("Equalized ch2", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Equalized ch2", h.getHistogramImage(channels2[0]));

	//merge 3 channels including the modified 1st channel into one image
	merge(channels2, 3, dst);

	// 평활화 히스토그램
	namedWindow("Equalized Histogram", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Equalized Histogram", h.getHistogramImage(dst));


	//컬러변환 to BGR
	cvtColor(dst, result2, COLOR_YCrCb2BGR);
	namedWindow("Equalized Image by YCrCb", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Equalized Image by YCrCb", result2);








	waitKey(0);
	return 0;

}


