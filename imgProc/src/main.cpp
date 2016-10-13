#include "WebCam.h"
#include "ImageProcCV.h"


int main()
{
//	WebCam *Camera = new WebCam("/dev/video0", 640, 480);
	ImageProcCV cv;
	cv.Display();
	return 0;
}