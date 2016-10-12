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

#include <linux/videodev2.h>

#define CLEAR(x) memset(&(x), 0, sizeof(x))


class WebCam{
private:
	char* devName;
	//buffer clasa Stefan
	unsigned int nBuffers;
	int fd;

	void ErrnoExit(const char *s);
	int xioctl(int desc, int req, void* arg);
	void InitDevice();
	void OpenDevice();
	
public:
	WebCam(const char* dev);
	~WebCam();

};



#endif //WEBCAM_H