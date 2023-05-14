#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat img, imgGary, imgBlur, imgCanny, imgDil, imgErode, imgResult;

int main()
{
	string path = "Resources/test.png";

	img = imread(path);

	//×ª»»Îª»Ò¶È
	cvtColor(img, imgGary, COLOR_BGR2GRAY);

	//¸ßË¹Ä£ºý
	GaussianBlur(imgGary, imgBlur, Size(7, 7), 5, 0);

	//ÂÖÀª¼ì²â
	Canny(imgBlur, imgCanny, 25, 45);

	Mat kernal1 = getStructuringElement(MORPH_RECT, Size(5, 5));
	Mat kernal2 = getStructuringElement(MORPH_RECT, Size(3,3));

	//ÅòÕÍ
	dilate(imgCanny, imgDil, kernal1);

	//ÇÖÊ´
	erode(imgDil, imgResult, kernal2);

	//Mat element = getStructuringElement(MORPH_RECT, Size(300, 300));
	//cv::morphologyEx(img, imgResult, MORPH_CLOSE, element);

	imshow("img", img);
	imshow("imgCanny", imgCanny);
	imshow("imgDil", imgDil);
	imshow("imgResult", imgResult);

	waitKey(0);
	return 0;
}