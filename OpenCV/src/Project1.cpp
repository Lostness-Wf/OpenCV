#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

vector<vector<int>> myColors{ {132, 149, 45, 191, 767, 224} /*purple*/ };
vector<Scalar> myColorValus{ {255, 0, 255} };

Mat img, imgHSV, mask;


void GetContours(Mat imgDil)
{

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);


	for (int i = 0; i < contours.size(); i++)
	{
		vector<vector<Point>> conPoly(contours.size());
		vector<Rect> boundRect(contours.size());

		int area = contourArea(contours[i]);
		cout << area << endl;

		if (area > 10)
		{
			float peri = arcLength(contours[i], true);
			//½üËÆ¶à±ßÐÎ
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, false);
			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);

			boundRect[i] = boundingRect(conPoly[i]);
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
		inRange(imgHSV, lower, upper, mask);
		imshow(to_string(i), mask);

		GetContours(mask);
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