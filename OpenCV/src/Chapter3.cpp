#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;

//////////   Resize and Crop   //////////
int main()
{
	std::string path = "Resources/test.png";
	Mat img = imread(path);
	Mat imgResize, imgCrop;

	//std::cout << img.size() << std::endl;
	//386 x 401

	//调整大小
	resize(img, imgResize, Size(), 0.5, 0.5);

	//裁剪
	Rect roi(100, 100, 200, 100);
	imgCrop = img(roi);

	imshow("Image", img);
	imshow("Image Resize", imgResize);
	imshow("Image Corp", imgCrop);

	waitKey(0);
	return 0;
}