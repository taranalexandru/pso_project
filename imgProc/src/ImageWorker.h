#ifndef CV_H
#define CV_H
#include "FaceDetector.h"
#include <cv.h>
#include <iostream>

using namespace std;
using namespace cv;

#define HEIGHT		640
#define WIDTH		480
#define TESTIMAGE "../res/test3.jpg"


class ImageWorker{
private:
	char* imgSource;
	FaceDetector* faceDetector;
public:
	ImageWorker();
	~ImageWorker();

	void process(uint8_t* image);
};

#endif