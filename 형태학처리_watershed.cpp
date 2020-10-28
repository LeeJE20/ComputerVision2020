#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace std;
using namespace cv;

//----Watershed segmentation class --//
class WatershedSegmenter {

private:

    cv::Mat markers;

public:

    void setMarkers(const cv::Mat& markerImage) {

        // Convert to image of ints
        markerImage.convertTo(markers, CV_32S);
    }

    cv::Mat process(const cv::Mat& image) {

        // Apply watershed
        cv::watershed(image, markers);

        return markers;
    }

    // Return result in the form of an image
    cv::Mat getSegmentation() {

        cv::Mat tmp;
        // all segment with label higher than 255
        // will be assigned value 255
        markers.convertTo(tmp, CV_8U);

        return tmp;
    }

    // Return watershed in the form of an image
    cv::Mat getWatersheds() {

        cv::Mat tmp;
        markers.convertTo(tmp, CV_8U, 255, 255);

        return tmp;
    }
};

int main(int argc, char** argv)
{
    Mat image, gray, binary;

    /// Load image
    image = imread("test.jpg", 1);   // Read the file   

    if (image.empty()) {                              // Check for invalid input   
        cout << "Could not open or find the image" << std::endl;
        return -1;
    }
    namedWindow("Display window", WINDOW_AUTOSIZE);
    imshow("Display window", image);

    cvtColor(image, gray, COLOR_BGR2GRAY);

    threshold(gray, binary, 120, 255, THRESH_BINARY_INV);

    // Display the binary image
    cv::namedWindow("Binary Image");
    cv::imshow("Binary Image", binary);


    // 침식-> 노이즈 제거
    // Eliminate noise and smaller objects
    cv::Mat fg;
    cv::erode(binary, fg, cv::Mat(), cv::Point(-1, -1), 6);

    // Display the foreground image
    cv::namedWindow("Foreground Image");
    cv::imshow("Foreground Image", fg);



    // 백그라운드. max가 128이다.
    // 팽창 이후 max가 128이 되게 한다.
    // Identify image pixels without objects
    cv::Mat bg;
    cv::dilate(binary, bg, cv::Mat(), cv::Point(-1, -1), 6);
    cv::threshold(bg, bg, 1, 128, cv::THRESH_BINARY_INV);

    // Display the background image
    cv::namedWindow("Background Image");
    cv::imshow("Background Image", bg);



    // 백그라운드랑 foreground를 합쳐 마커를 만듦
    //Show markers image
    cv::Mat markers(binary.size(), CV_8U, cv::Scalar(0));
    markers = fg + bg;
    cv::namedWindow("Markers");
    cv::imshow("Markers", markers);






    // Create watershed segmentation object
    WatershedSegmenter segmenter;

    // Set markers and process
    segmenter.setMarkers(markers);
    Mat res = segmenter.process(image);

    //// Display segmentation result
    //cv::namedWindow("Pre - Segmentation");
    //cv::imshow("Pre - Segmentation",res);

    // Display segmentation result
    cv::namedWindow("Segmentation");
    cv::imshow("Segmentation", segmenter.getSegmentation());





    // Display watersheds
    cv::namedWindow("Watersheds");
    cv::imshow("Watersheds", segmenter.getWatersheds());

    waitKey(0);
    return 0;
}