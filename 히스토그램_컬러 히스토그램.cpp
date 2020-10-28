#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include<opencv2/imgproc.hpp>
using namespace cv;
using namespace std;
// ~~화소점처리 실습


MatND getHistogramCImage(const Mat& image);



class Histogram1D {
private:
	int histSize[1]; // 히스토그램 빈도수
	float hranges[2]; // 히스토그램 최소/최대 화소값
	const float* ranges[1];
	int channels[1]; // 1채널만 사용
public:
	Histogram1D() { // 1차원 히스토그램을 위한 인자 준비
		histSize[0] = 256;
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

class ColorHistogram {
private:
	//int histSize[1]; // 히스토그램 빈도수
	//float hranges[2]; // 히스토그램 최소/최대 화소값
	//const float* ranges[1];
	//int channels[1]; // 1채널만 사용
	//Histogram1D h;
public:
	//ColorHistogram() { // 1차원 히스토그램을 위한 인자 준비
	//	histSize[0] = 256;
	//	hranges[0] = 0.0;
	//	hranges[1] = 255.0;
	//	ranges[0] = hranges;
	//	channels[0] = 0;
	//}

	// 히스토그램 계산
	MatND getHistogram(const Mat& image) {
		Mat bgr_planes[3], hist;
		split(image, bgr_planes);

		///// Establish the number of bins
		//int histSize = 256;
		///// Set the ranges ( for B,G,R) )
		//float range[] = { 0, 256 };
		//const float* histRange = { range };
		//bool uniform = true; bool accumulate = false;
		//Mat b_hist, g_hist, r_hist;
		///// Compute the histograms:
		//calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
		//calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
		//calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);		// 인자 값 : 이미지, 단일영상, 대상채널, 마스크 사용안함, 결과히스토그램,
		//



		// ---- Histogram1D를 이용한 구현 ----
		Histogram1D h;

		bgr_planes[0] = h.getHistogram(bgr_planes[0]);
		bgr_planes[1] = h.getHistogram(bgr_planes[1]);
		bgr_planes[2] = h.getHistogram(bgr_planes[2]);

		// ---- Histogram1D를 이용한 구현 ----

		merge(bgr_planes, 3, hist);

		return hist;
	}


	MatND getHistogramCImage(const Mat& image) {
		///// Separate the image in 3 places ( B, G and R )
		//Mat bgr_planes[3];
		//split(image, bgr_planes);
		///// Establish the number of bins
		//int histSize = 256;
		///// Set the ranges ( for B,G,R) )
		//float range[] = { 0, 256 };
		//const float* histRange = { range };
		//bool uniform = true; bool accumulate = false;
		//Mat b_hist, g_hist, r_hist;
		///// Compute the histograms:
		//calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
		//calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
		//calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);
		//
		int histSize = 256;
		Mat b_hist, g_hist, r_hist, hist, bgr_planes[3];

		hist = getHistogram(image);
		split(hist, bgr_planes);
		b_hist = bgr_planes[0];
		g_hist = bgr_planes[1];
		r_hist = bgr_planes[2];

		// Draw the histograms for B, G and R
		int hist_w = 512; int hist_h = 400;
		int bin_w = cvRound((double)hist_w / histSize);

		Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));
		/// Normalize the result to [ 0, histImage.rows ]
		normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
		normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
		normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
		/// Draw for each channel
		for (int i = 1; i < histSize; i++)
		{
			line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
				Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))),
				Scalar(255, 0, 0), 2, 8, 0);
			line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
				Point(bin_w * (i), hist_h - cvRound(g_hist.at<float>(i))),
				Scalar(0, 255, 0), 2, 8, 0);
			line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
				Point(bin_w * (i), hist_h - cvRound(r_hist.at<float>(i))),
				Scalar(0, 0, 255), 2, 8, 0);
		}
		return histImage;
	}
};




// argument를 입력 받게 하자!
// argument 첫번째, 두번째.. 갖고옴
int main(int argc, char** argv)
{
	Mat image, dst;
	/// Load image
	image = imread("test.jpg", 1); // Read the file
	if (image.empty()) { // Check for invalid input
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Display window", image);
	ColorHistogram h;
	MatND histo = h.getHistogram(image); // 히스토그램 계산
	MatND Chist = h.getHistogramCImage(image);
	// 히스토그램을 영상으로 띄우기
	namedWindow("Color Histogram");
	imshow("Color Histogram", Chist);
	waitKey(0);
	return 0;
}


