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

	//ת��Ϊ�Ҷ�
	cvtColor(img, imgGary, COLOR_BGR2GRAY);
	//��˹ģ��
	GaussianBlur(img, imgBlur, Size(7, 7), 5, 0);
	//�������
	Canny(imgBlur, imgCanny, 20, 45);

	//�Ŵ�������
	Mat kernal = getStructuringElement(MORPH_RECT, Size(5, 5));
	dilate(imgCanny, imgDil, kernal);
	//��ʴ������
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