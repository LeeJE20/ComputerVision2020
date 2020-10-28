#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include<opencv2/imgproc.hpp>
using namespace cv;
using namespace std;


//컬러채널 분리

// argument를 입력 받게 하자!
// argument 첫번째, 두번째.. 갖고옴
int main(int argc, char** argv)
{
	//--- Color channel Separation/Mixing -----//
	if (argc != 2)
	{
		cout << " Usage: Give an input image file name...!!!" << endl;
		return -1;
	}
	Mat src = imread(argv[1], 1);
	if (!src.data)
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	namedWindow("src", 1);
	imshow("src", src);


	// Split the image into different channels and show them...!!!
	Mat rgbChannels[3];
	split(src, rgbChannels);
	namedWindow("Blue", 1);
	imshow("Blue", rgbChannels[0]);
	namedWindow("Green", 1);
	imshow("Green", rgbChannels[1]);
	namedWindow("Red", 1);
	imshow("Red", rgbChannels[2]);
	// Show individual channels
	Mat g, fin_img;
	g = Mat::zeros(Size(src.cols, src.rows), CV_8UC1);



	//-- Showing Red Channel
//-- G and B channels are kept as zero matrix for visualperception
	{
		vector<Mat> channels;
		channels.push_back(g);
		channels.push_back(g);
		channels.push_back(rgbChannels[2]);
		/// Merge the three channels
		merge(channels, fin_img);
		namedWindow("R", 1);
		imshow("R", fin_img);
	}
	// Showing Green Channel
	{
		vector<Mat> channels;
		channels.push_back(g);
		channels.push_back(rgbChannels[1]);
		channels.push_back(g);
		merge(channels, fin_img);
		namedWindow("G", 1); 
		imshow("G", fin_img);
	}

	// Showing Blue Channel
	{
		vector<Mat> channels;
		channels.push_back(rgbChannels[0]);
		channels.push_back(g);
		channels.push_back(g);
		merge(channels, fin_img);
		namedWindow("B", 1);
		imshow("B", fin_img);
	}
	waitKey(0);


	return 0;
}