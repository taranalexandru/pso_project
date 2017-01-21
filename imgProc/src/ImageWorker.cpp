#include "ImageWorker.h"



ImageWorker :: ImageWorker()
{
	faceDetector = new FaceDetector();
	namedWindow("Face Tracker");
}

ImageWorker :: ~ImageWorker()
{
	if(imgSource)
		delete[] imgSource;
}

void ImageWorker :: process(uint8_t* image)
{
	Mat img(Size(HEIGHT, WIDTH), CV_8UC3, image);
	Mat dec = imdecode(img, CV_LOAD_IMAGE_COLOR);
	faceDetector->processFrame(dec);	
	imshow("Face Tracker",dec);
	return true;
}