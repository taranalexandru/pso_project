#include "FrameConverter.h"
#include "WebCam.h"

int main()
{

	WebCam *Camera = new WebCam("/dev/video0", 640, 480);
	UString* frame = Camera->GetFrame();
	printf("\n%d\n",frame->getLength());
	FILE* f=fopen("img01.yuv","w");
	fwrite(frame->getBuffer(), frame->getLength(), 1, f);
	FrameConverter* conv = new FrameConverter();
	conv->StartConversion((char*)"img01.rgb",*frame);
	delete conv;
	fclose(f);
	return 0;
}