#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include<opencv2/imgproc.hpp>
using namespace cv;
using namespace std;

// 코너 검출
// 형태학적 처리


//--Class for Corner detection ---//
class MorphoFeatures {
private:
	// threshold to produce binary image
	int threshold;
	// structuring elements used in corner detection
	cv::Mat cross;
	cv::Mat diamond;
	cv::Mat square;
	cv::Mat x;
	void applyThreshold(cv::Mat& result) {
		// Apply threshold on result
		if (threshold > 0)
			cv::threshold(result, result, threshold, 255, cv::THRESH_BINARY_INV);
	}
public:
	MorphoFeatures() : threshold(-1), cross(5, 5, CV_8U, cv::Scalar(0)),
		diamond(5, 5, CV_8U, cv::Scalar(1)),
		square(5, 5, CV_8U, cv::Scalar(1)),
		x(5, 5, CV_8U, cv::Scalar(0)) {
		// Creating the cross-shaped structuring element
		for (int i = 0; i < 5; i++) {
			cross.at<uchar>(2, i) = 1;
			cross.at<uchar>(i, 2) = 1;
		}
		// Creating the diamond-shaped structuring element
		diamond.at<uchar>(0, 0) = 0;
		diamond.at<uchar>(0, 1) = 0;
		diamond.at<uchar>(1, 0) = 0;
		diamond.at<uchar>(4, 4) = 0;
		diamond.at<uchar>(3, 4) = 0;
		diamond.at<uchar>(4, 3) = 0;
		diamond.at<uchar>(4, 0) = 0;
		diamond.at<uchar>(4, 1) = 0;
		diamond.at<uchar>(3, 0) = 0;
		diamond.at<uchar>(0, 4) = 0;
		diamond.at<uchar>(0, 3) = 0;
		diamond.at<uchar>(1, 4) = 0;
		// Creating the x-shaped structuring element
		for (int i = 0; i < 5; i++) {
			x.at<uchar>(i, i) = 1;
			x.at<uchar>(4 - i, i) = 1;
		}
	}

	void setThreshold(int t) {
		threshold = t;
	}
	int getThreshold() const {
		return threshold;
	}
	cv::Mat getEdges(const cv::Mat& image) {
		// Get the gradient image
		cv::Mat result;
		cv::morphologyEx(image, result, cv::MORPH_GRADIENT, cv::Mat());
		// Apply threshold to obtain a binary image
		applyThreshold(result);
		return result;
	}




	cv::Mat getCorners(const cv::Mat& image) {
		cv::Mat result;
		// Dilate with a cross
		cv::dilate(image, result, cross);
		// Erode with a diamond
		cv::erode(result, result, diamond);
		cv::Mat result2;
		// Dilate with a X
		cv::dilate(image, result2, x);
		// Erode with a square
		cv::erode(result2, result2, square);
		// Corners are obtained by differencing
		// the two closed images
		cv::absdiff(result2, result, result);
		// Apply threshold to obtain a binary image
		applyThreshold(result);
		return result;
	}


	void drawOnImage(const cv::Mat& binary, cv::Mat& image) {
		cv::Mat_<uchar>::const_iterator it = binary.begin<uchar>();
		cv::Mat_<uchar>::const_iterator itend = binary.end<uchar>();
		// for each pixel
		for (int i = 0; it != itend; ++it, ++i) {
			if (!*it)
				cv::circle(image, cv::Point(i % image.step, i / image.step), 5, cv::Scalar(255, 0, 0));
		}
	}
};



// argument를 입력 받게 하자!
// argument 첫번째, 두번째.. 갖고옴
// src = imread(argv[1], 1);
int main(int argc, char** argv)
{
	Mat image;
	/// Load image
	image = imread(argv[1], 0); // Read the file
	if (image.empty()) { // Check for invalid input
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	// Create a window for display.
	namedWindow("Display window", WINDOW_AUTOSIZE);
	imshow("Display window", image);
	//--클래스 객체 선언 --//
	MorphoFeatures morpho;
	morpho.setThreshold(40);
	//--에지 가져오기 --//
	// Get the edges
	Mat edges;
	edges = morpho.getEdges(image);
	// Display the edge image
	namedWindow("Edge Image");
	imshow("Edge Image", edges);
	//-- Get the corners--//
	morpho.setThreshold(-1);
	cv::Mat corners;
	corners = morpho.getCorners(image);
	cv::morphologyEx(corners, corners, cv::MORPH_TOPHAT, cv::Mat());
	cv::threshold(corners, corners, 40, 255, cv::THRESH_BINARY_INV);


	// Display the corner image
	cv::namedWindow("Corner Image");
	cv::imshow("Corner Image", corners);
	// Display the corner on the image
	morpho.drawOnImage(corners, image);
	cv::namedWindow("Corners on Image");
	cv::imshow("Corners on Image", image);
	waitKey(0);
	return 0;
}

