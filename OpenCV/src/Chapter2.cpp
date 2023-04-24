#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;

//////////   Basic Functions   //////////
int main()
{
	std::string path = "Resources/test.png";
	Mat img = imread(path);
	Mat imgGary;
	Mat imgBlur;
	Mat imgCanny;
	Mat imgDil;
	Mat imgErode;

	//转换为灰度
	cvtColor(img, imgGary, COLOR_BGR2GRAY);
	//高斯模糊
	GaussianBlur(img, imgBlur, Size(7, 7), 5, 0);
	//轮廓检测
	Canny(imgBlur, imgCanny, 20, 45);

	//放大轮廓线
	Mat kernal = getStructuringElement(MORPH_RECT, Size(5, 5));
	dilate(imgCanny, imgDil, kernal);
	//侵蚀轮廓线
	dilate(imgDil, imgErode, kernal);

	imshow("image", img);
	imshow("image Gary", imgGary);
	imshow("image Blur", imgBlur);
	imshow("image Canny", imgCanny);
	imshow("image Dilation", imgDil);
	imshow("image Erode", imgErode);
	waitKey(0);
	return 0;
}