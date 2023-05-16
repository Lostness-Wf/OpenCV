#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;

const std::string path = "Resources/2.jpg";

Mat img;
Mat imgHoughTrans, imgCropTrans, imgCannyTrans, imgtemp;

Mat ImgCutCir(Mat image)
{
	Mat grayImg;
	cvtColor(image, grayImg, COLOR_BGR2GRAY);

	std::vector<Vec3f>circles;
	HoughCircles(grayImg, circles, HOUGH_GRADIENT, 1, 10, 110, 58, 580, 650);
	Mat houghcircle = image.clone();
	for (int i = 0; i < circles.size(); i++) {
		circle(houghcircle, Point(circles[i][0], circles[i][1]), circles[i][2], Scalar(0, 0, 255), 7);
	}

	Mat image1(image.rows, image.cols, image.type(), Scalar(0, 255, 0));
	Point center = Point(circles[0][0], circles[0][1]);
	int radius = circles[0][2];
	circle(image, center, radius, Scalar(0, 200, 100), 2, 8, 0);
	for (int x = 0; x < image.cols; x++) {
		for (int y = 0; y < image.rows; y++) {
			int temp = ((x - center.x) * (x - center.x) + (y - center.y) * (y - center.y));
			if (temp < (radius * radius)) {
				image1.at <Vec3b>(Point(x, y))[0] = image.at <Vec3b>(Point(x, y))[0];
				image1.at <Vec3b>(Point(x, y))[1] = image.at <Vec3b>(Point(x, y))[1];
				image1.at <Vec3b>(Point(x, y))[2] = image.at <Vec3b>(Point(x, y))[2];
			}
		}
	}

	resize(houghcircle, imgHoughTrans, Size(540, 960));
	resize(image1, imgCropTrans, Size(540, 960));
	imshow("imgHoughcircle", imgHoughTrans);
	imshow("imgCrop", imgCropTrans);
	return image1;
}

void GetContrours(Mat img)
{
	Mat imgGray, imgBlur, imgCanny, imgThr, imgClose;
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	threshold(imgGray, imgThr, 100, 255, THRESH_BINARY);

	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
	cv::morphologyEx(imgThr, imgClose, MORPH_CLOSE, element);

	Canny(imgClose, imgCanny, 50, 60, 7);

	std::vector<std::vector<Point>> contours;
	std::vector<Vec4i> hierarchy;

	findContours(imgCanny, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	drawContours(imgCanny, contours, -1, Scalar(255, 0, 255), 2);

	resize(imgCanny, imgCannyTrans, Size(540, 960));
	imshow("imgCanny", imgCannyTrans);
};

int main() {
	img = imread(path);

	Mat imgCrop = ImgCutCir(img);	

	GetContrours(imgCrop);

	waitKey(0);
	return 0;
}