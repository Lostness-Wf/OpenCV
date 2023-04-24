#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;

//////////   Images   //////////
//int main()
//{
//	std::string path = "Resources/test.png";
//	cv::Mat img = cv::imread(path);
//	cv::imshow("image", img);
//	cv::waitKey(0);
//	return 0;
//}


//////////   Video   //////////
//int main()
//{
//	std::string path = "Resources/test_video.mp4";
//	VideoCapture cap(path);
//	Mat img;
//
//	while (true)
//	{
//
//		cap.read(img);
//
//		imshow("image", img);
//		waitKey(20);
//	}
//		return 0;
//}


//////////   Webcam   //////////
int main()
{
	VideoCapture cap(0);
	Mat img;

	while (true)
	{

		cap.read(img);

		imshow("image", img);
		waitKey(1);
	}
	return 0;
}