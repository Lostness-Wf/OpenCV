#include<opencv2\\core\\core.hpp>
#include<opencv2\\highgui\\highgui.hpp>
#include<opencv2\\imgproc\\imgproc.hpp>
#include<iostream>
using namespace cv;
using namespace std;

const std::string path = "Resources/1.jpg";

int main(int argc, char* argv[])
{
	Mat image = imread(path);
	Mat image1(image.rows, image.cols, image.type(), Scalar(180, 120, 50));
	Point center(image.cols / 2, image.rows / 2);
	int radius = 200;
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

	imshow("temp", image1);
	waitKey(0);
	return 0;
}