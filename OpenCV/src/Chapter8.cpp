#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>

#include <iostream>

using namespace cv;

//////////   Images   //////////
int main()
{
	VideoCapture cap(0);
	Mat img;

	CascadeClassifier faceCascade;
	faceCascade.load("Resources/haarcascade_frontalface_default.xml");
	if (faceCascade.empty()) { std::cout << "XML file not loaded" << std::endl; }

	std::vector<Rect> faces;

	while (true)
	{
		cap.read(img);

		faceCascade.detectMultiScale(img, faces, 1.2, 10);
		for (int i = 0; i < faces.size(); ++i)
		{
			rectangle(img, faces[i].tl(),faces[i].br(), Scalar(255, 0, 255), 3);
		}

		imshow("image", img);
		waitKey(1);
	}
	return 0;
}