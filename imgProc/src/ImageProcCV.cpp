#include "ImageProcCV.h"


ImageProcCV :: ImageProcCV()
{
	imgSource = strdup("/home/alex/pso/pso_project/imgProc/res/img01.jpg");
}

void ImageProcCV :: GetNextImage()
{
	if(imgSource[43] < '9')
		imgSource[43]++; 
}

ImageProcCV :: ~ImageProcCV()
{
	if(imgSource)
		delete[] imgSource;
}

void ImageProcCV :: Display()
{
	IplImage *image;
	cvNamedWindow("Test");
	for(int i = 0; i < 9; i++)
	{
		image = cvLoadImage(imgSource);
		cvShowImage("Test",image);
		cvWaitKey(60);
		GetNextImage();
	}
}