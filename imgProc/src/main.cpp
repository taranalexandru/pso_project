#include "WebCam.h"


int main()
{
	WebCam *Camera = new WebCam("/dev/video0", 640, 480);

	return 0;
}