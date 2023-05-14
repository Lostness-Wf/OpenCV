#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

using namespace cv;

Mat img, imgHSV, imgMask;
std::vector<std::vector<int>> myColors{ {132, 149, 45, 191, 767, 224} };

void GetContours(Mat imgDil)
{
	std::vector<std::vector<Point>> contours;
	std::vector<Vec4i> hierarchy;

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	std::vector<std::vector<Point>> conPoly(contours.size());
	std::vector<Rect> boundRect(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);
		std::cout << area << std::endl;

		if (area > 50)
		{
			float peri = arcLength(contours[i], true);
			//近似多边形
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			//绘制轮廓
			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
			boundRect[i] = boundingRect(conPoly[i]);

			//绘制包裹框
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 3);
		}
	}
}

void FindColor(Mat img)
{
	cvtColor(img, imgHSV, COLOR_RGB2HSV);

	for (int i = 0; i < myColors.size(); ++i)
	{
		Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);
		Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);
		inRange(imgHSV, lower, upper, imgMask);
		imshow(std::to_string(i), imgMask);

		GetContours(imgMask);
	}
}

VideoCapture cap(0);

int main()
{

	while (true)
	{
		cap.read(img);
		FindColor(img);

		imshow("Image", img);

		waitKey(1);
	}

	return 0;
}