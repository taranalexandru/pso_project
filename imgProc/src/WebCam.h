#ifndef WEBCAM_H
#define WEBCAM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <getopt.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include "UString.h"

#include <linux/videodev2.h>

#define CLEAR(x) memset(&(x), 0, sizeof(x))


class WebCam{
private:
	char* devName;
	UString *buffers;
	int nBuffers;
	int fd;
	int width, height;

	void ErrnoExit(const char *s);
	int xioctl(int desc, int req, void* arg);
	void InitDevice();
	void OpenDevice();
	void StartCapturing();
	void StopCapturing();

public:
	WebCam(const char* dev, int width, int height);
	~WebCam();

	UString* GetFrame();
};



#endif //WEBCAM_H