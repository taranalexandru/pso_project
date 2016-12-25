#include "FrameConverter.h"
#include "WebCam.h"
//#include "ImageProcCV.h"
#include "FrameCompresser.h"

int main()
{
	WebCam *Camera = new WebCam("/dev/video0", 640, 480);
	UString* frame = Camera->GetFrame();
	printf("\n%d\n",frame->getLength());
	FILE* f=fopen("img01.yuv","w");
	fwrite(frame->getBuffer(), frame->getLength(), 1, f);
	FrameConverter* conv = new FrameConverter();
	conv->StartConversion((char*)"img01.rgb",*frame);

	FrameCompresser* comp = new FrameCompresser((char*)"img01.rgb");
	comp->Compress((char*)"img01.jpg");
	comp->Decompress((char*)"img01.jpg",(char*)"img01x.rgb");

	//delete conv;
	//fclose(f);

	//WebCam *Camera = new WebCam("/dev/video0", 640, 480);
	//ImageProcCV cv;
	//cv.Display();

	return 0;
}