#ifndef CV_H
#define CV_H
#include <highgui.h>
#include <videoio.hpp>
#include <cv.h>
#include <core.hpp>
#include <iostream>

using namespace std;
using namespace cv;

class ImageProcCV{
private:
	cv::VideoCapture sequence;

	char* imgSource;
	void GetNextImage();
public:
	ImageProcCV();
	~ImageProcCV();

	void Display();
};

#endif