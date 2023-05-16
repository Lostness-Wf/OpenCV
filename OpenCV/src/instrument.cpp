#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;

const std::string path = "Resources/2.jpg";

Mat img, imgGray, imgCanny, imgThr, imgClose, imgBlur;

void ImageProcess(Mat img)
{
	cvtColor(img, imgGray, COLOR_BGR2GRAY);

	GaussianBlur(imgGray, imgBlur, Size(7, 7), 5);

	Canny(imgBlur, imgCanny, 50, 80, 3);
}

int main()
{
	img = imread(path);
	ImageProcess(img);

	Mat imgTrans, imgGrayTrans, imgCannyTrans, imgThrTrans, imgCloseTrans;

	resize(img, imgTrans, Size(540, 960));
	resize(imgGray, imgGrayTrans, Size(540, 960));
	resize(imgCanny, imgCannyTrans, Size(540, 960));

	imshow("img", imgTrans);
	imshow("imgGray", imgGrayTrans);
	imshow("imgCanny", imgCannyTrans);

	waitKey(0);
	return 0;
}