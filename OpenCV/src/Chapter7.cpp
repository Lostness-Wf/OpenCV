#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;

Mat imgGary, imgBlur, imgCanny, imgDil, imgErode;

void GetContours(Mat imgDil, Mat img)
{
	std::vector<std::vector<Point>> contours;
	std::vector<Vec4i> hierarchy;

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	std::vector<std::vector<Point>> conPoly(contours.size());
	std::vector<Rect> boundRect(contours.size());
	std::string objType;

	for (int i = 0; i < contours.size(); ++i)
	{
		int area = contourArea(contours[i]);

		if (area > 2000)
		{
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);

			boundRect[i] = boundingRect(conPoly[i]);

			int objCor = (int)conPoly[i].size();

			if (objCor == 3) { objType = "Tri"; }
			if (objCor == 4) { objType = "Rect"; }
			if (objCor > 4) { objType = "Circle"; }

			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
			putText(img, objType, { boundRect[i].x, boundRect[i].y - 5 }, FONT_HERSHEY_DUPLEX, 0.75, Scalar(0, 69, 255), 2);
		}
	}
}

int main()
{
	std::string path = "Resources/shapes.png";
	Mat img = imread(path);


	//转换为灰度
	cvtColor(img, imgGary, COLOR_BGR2GRAY);
	//高斯模糊
	GaussianBlur(imgGary, imgBlur, Size(3, 3), 3, 0);
	//轮廓检测
	Canny(imgBlur, imgCanny, 25, 75);
	//放大轮廓线
	Mat kernal = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernal);

	GetContours(imgDil, img);

	imshow("image", img);
	//imshow("image Gray", imgGary);
	//imshow("image Blur", imgBlur);
	//imshow("image Canny", imgCanny);
	//imshow("image Dil", imgDil);

	waitKey(0);


	return 0;
}