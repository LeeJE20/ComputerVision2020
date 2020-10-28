#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include<opencv2/imgproc.hpp>
#include<cmath>
using namespace cv;
using namespace std;

// 솔트앤 페퍼 영상을 평균, 가우시안, 미디안 필터로 블러링 해보기

void salt(Mat& img, int n); // 잡음 추가 함수 선언

int row, column, n, m;


// argument를 입력 받게 하자!
// argument 첫번째, 두번째.. 갖고옴
int main(int argc, char** argv)
{
	Mat image, sp, dst, dst1;
	/// Load image
	image = imread("pepper.bmp", 1); // Read the file
	if (image.empty()) { // Check for invalid input
		cout << "Could not open or find the image"
			<< std::endl;
		return -1;
	}

	cvtColor(image, image, COLOR_BGR2GRAY);

	// Display the S&P image
	cv::namedWindow("original Image");
	cv::imshow("original Image", image);


	sp = image.clone();
	//솔트앤 페퍼 영상 만들기
	// make a noise image
	salt(sp, 20000);
	// Display the S&P image
	cv::namedWindow("S&P Image");
	cv::imshow("S&P Image", sp);


	//평균 필터
	// Blur the image with a mean filter
	cv::blur(sp, dst, cv::Size(5, 5));
	// Display the blurred image




	//미디안 필터
	// Applying a median filter
	cv::medianBlur(sp, dst1, 5);
	// Display the blurred image





	row = image.rows;
	column = image.cols;
	n = row * column;
	m = n;


	int nl = image.rows; // 행 개수
	int nc = image.cols * image.channels(); // 각 행의 데이터 개수



	double mse = 0;
	double psnr = 0;

	double pow255 = pow(255, 2);
	// 블러




	for (int j = 0; j < nl; j++)
	{
		//j열의 주소(nc개만큼) 가져오기
		uchar* data = image.ptr<uchar>(j);
		uchar* datablur = dst.ptr<uchar>(j);
		for (int i = 0; i < nc; i++)
		{

			mse = mse + pow(data[i] - datablur[i], 2);
		}

	}
	cout << "mse: " << mse << endl;


	double nm = nl * nc;
	cout << "nm: " << nm << endl;
	//mse = mse / (nm);

	cout << "mse: " << mse << endl;

	//psnr = 10 * (2* log10(255) - log10(mse));

	psnr = 10 * (2 * log10(255) - log10(mse / (nm)));
	cout << psnr << endl;


	string text = "PSNR = " + to_string(psnr);
	int fontFace = FONT_HERSHEY_PLAIN;
	double fontScale = 2;
	int thickness = 3;

	int baseline = 0;
	Size textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
	baseline += thickness;
	// center the text
	Point textOrg((image.cols - textSize.width) / 2, (image.rows + textSize.height) / 1.2);


	// then put the text itself
	putText(dst, text, textOrg, fontFace, fontScale, Scalar(255, 130, 130), thickness, 8);
	//namedWindow("Display text");
	//imshow("Display text", dst);


	cv::namedWindow("Mean filtered S&P Image");
	cv::imshow("Mean filtered S&P Image", dst);



	mse = 0;
	psnr = 0;

	for (int j = 0; j < nl; j++)
	{
		//j열의 주소(nc개만큼) 가져오기
		uchar* data = image.ptr<uchar>(j);
		uchar* datablur = dst1.ptr<uchar>(j);
		for (int i = 0; i < nc; i++)
		{

			mse = mse + pow(data[i] - datablur[i], 2);
		}

	}
	cout << "mse: " << mse << endl;



	cout << "nm: " << nm << endl;
	//mse = mse / (nm);

	cout << "mse: " << mse << endl;
	mse = mse / nm;
	//psnr = 10 * (2* log10(255) - log10(mse));

	//psnr = 10 * (2 * log10(255) - log10(mse / (nm)));

	psnr = 10 * (log10((255 * 255) / mse));
	cout << psnr << endl;


	text = "PSNR = " + to_string(psnr);


	putText(dst1, text, textOrg, fontFace, fontScale, Scalar(255, 130, 130), thickness, 8);



	cv::namedWindow("Median filtered S&P Image");
	cv::imshow("Median filtered S&P Image", dst1);













	waitKey(0);
	return 0;


}

void salt(Mat& img, int n)
{
	for (int k = 0; k < n; k++) {
		int i = rand() % img.cols;
		int j = rand() % img.rows;
		if (img.channels() == 1) { // Gray scale image
			img.at<uchar>(j, i) = 255;
		}
		else if (img.channels() == 3) { // Color image
			img.at<Vec3b>(j, i)[0] = 255;
			img.at<Vec3b>(j, i)[1] = 255;
			img.at<Vec3b>(j, i)[2] = 255;
		}
	}
}
