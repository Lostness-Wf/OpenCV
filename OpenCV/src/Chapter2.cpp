#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;

//////////   Basic Functions   //////////
int main()
{
	VideoCapture cap(0);
	Mat img;

	//std::string path = "Resources/test.png";
	//Mat img = imread(path);
	Mat imgGary;
	Mat imgBlur;
	Mat imgCanny;
	Mat imgDil;
	Mat imgErode;

	while (true)
{
	cap.read(img);
	
		//ת��Ϊ�Ҷ�
		cvtColor(img, imgGary, COLOR_BGR2GRAY);
		//��˹ģ��
		GaussianBlur(imgGary, imgBlur, Size(7, 7), 5, 0);
		//�������
		Canny(imgBlur, imgCanny, 25, 45);
	
		//�Ŵ�������
		//Mat kernal = getStructuringElement(MORPH_RECT, Size(5, 5));
		//dilate(imgCanny, imgDil, kernal);
		//��ʴ������
		//dilate(imgDil, imgErode, kernal);
	
		imshow("image", img);
		imshow("image Gary", imgGary);
		imshow("image Blur", imgBlur);
		imshow("image Canny", imgCanny);
		//imshow("image Dilation", imgDil);
		//imshow("image Erode", imgErode);
		waitKey(1);
}
	return 0;
}