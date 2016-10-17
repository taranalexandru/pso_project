#include "FrameConverter.h"
#include "WebCam.h"
#include "ImageProcCV.h"

int main()
{
<<<<<<< HEAD

	WebCam *Camera = new WebCam("/dev/video0", 640, 480);
	UString* frame = Camera->GetFrame();
	printf("\n%d\n",frame->getLength());
	FILE* f=fopen("img01.yuv","w");
	fwrite(frame->getBuffer(), frame->getLength(), 1, f);
	FrameConverter* conv = new FrameConverter();
	conv->StartConversion((char*)"img01.rgb",*frame);
	delete conv;
	fclose(f);
=======
//	WebCam *Camera = new WebCam("/dev/video0", 640, 480);
	ImageProcCV cv;
	cv.Display();
>>>>>>> abdcf540ea40a2c9142088b9dd99f82fe672c2d9
	return 0;
}