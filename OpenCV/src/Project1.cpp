#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat img, imgHSV, mask;

vector<vector<int>> myColors{ {132, 149, 45, 191, 767, 224} /*purple*/ };
vector<Scalar> myColorValues{ {255, 0, 255} };
vector<vector<int>> newPoints;

Point GetContours(Mat imgDil)
{

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());

	Point myPoint(0.0);

	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);
		cout << area << endl;

		if (area > 5)
		{
			float peri = arcLength(contours[i], true);
			//近似多边形
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			//绘制轮廓
			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);

			boundRect[i] = boundingRect(conPoly[i]);
			myPoint.x = boundRect[i].x + boundRect[i].width / 2;
			myPoint.y = boundRect[i].y;

			//绘制包裹框
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 3);
		}
	}
	return myPoint;
}

vector<vector<int>> FindColor(Mat img)
{
	//转换为灰度
	cvtColor(img, imgHSV, COLOR_RGB2HSV);

	for (int i = 0; i < myColors.size(); ++i)
	{
		Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);
		Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);
		inRange(imgHSV, lower, upper, mask);
		imshow(to_string(i), mask);

		Point myPoint = GetContours(mask);

		if (myPoint.x != 0 && myPoint.y != 0)
		{
			newPoints.push_back({ myPoint.x, myPoint.y, i });
		}
	}
	return newPoints;
}

void DrawOnCanvas(vector<vector<int>> newPoints, vector<Scalar> myColorValues)
{
	for (int i = 0; i < newPoints.size(); ++i)
	{
		circle(img, Point(newPoints[i][0], newPoints[i][1]), 3, myColorValues[newPoints[i][2]], FILLED);
	}
}

VideoCapture cap(0);

int main()
{

	while (true)
	{
		cap.read(img);
		newPoints = FindColor(img);
		DrawOnCanvas(newPoints, myColorValues);

		imshow("Image", img);
		waitKey(1);
	}

	return 0;
}