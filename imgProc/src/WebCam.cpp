#include "WebCam.h"


WebCam :: WebCam(const char* s)
{
	devName = strdup(s);
}

WebCam :: ~WebCam()
{
	if(devName)
		delete[] devName;
}

void WebCam :: ErrnoExit(const char* s)
{
	fprintf(stderr, "%s error %d, %s\n", s, errno, strerror(errno));
	exit(EXIT_FAILURE);
}

int WebCam :: xioctl(int desc, int req, void* arg)
{
	int r;

	do
	{
		r = ioctl(desc, req, arg);
	}while(r==-1 && EINTR == errno);

}

void WebCam :: OpenDevice()
{
	fd = open(devName, O_RDWR, 0);

	if(fd == -1)
	{
		fprintf(stderr, "Cannot open '%s'\n", devName);
		exit(EXIT_FAILURE);
	}

}

void InitDevice()
{
	struct v4l2_capability cap;
	struct v4l2_format fmt;
    
    // Verificare capabilitati camerea
	if(xioctl(fd, VIDIOC_QUERYCAP, &cap) == -1)
	{
		fprintf(stderr, "%s is not V4L2 device\n", devName);
		exit(EXIT_FAILURE);
	}

    // Daca suporta captura video 
	if(!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE))
	{
		fprintf(stderr, "%s is not video capture device\n", devName);
		exit(EXIT_FAILURE);
	}
  
    // Daca suporta streaming
	if(!(cap.capabilities & V4L2_CAP_STREAMING))
	{
		fprintf(stderr, "%s does not support streaming\n", devName);
		exit(EXIT_FAILURE);
	}
    
    // Stabilire format pixeli
	CLEAR(fmt);

	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fmt.fmt.pix.width = this->width;
	fmt.fmt.pix.height = this->height;
	fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
	fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;

	if(xioctl(fd, VIDIOC_S_FMT, &fmt) == -1)
	{
		fprintf(stderr, "Error seting format\n");
		exit(EXIT_FAILURE);
	}

	// Mapare camere pe memoria din user space
	struct v4l2_requestbuffers req;

	req.count = 2;
	req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	req.memory = V4L2_MEMORY_MMAP;

	if(xioctl(fd, VIDIOC_REQBUFS, &req) == -1)
	{
		fprintf(stderr, "%s does not support memory mapping\n", devName);
		exit(EXIT_FAILURE);
	}

	//alocare buffer + mapare





}
	
void WebCam :: StartCapturing()
{
	enum v4l2_buf_type type;
	for(int i = 0; i < nBuffers; i++)
	{
		struct v4l2_buffer buf;

		CLEAR(buf);

		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_MMAP;
		buf.index = i;

		// Adaugare buffer in coada
		if(xioctl(fd, VIDIOC_QBUF, &buf) == -1)
		{
			fprintf(stderr, "Could not queue the buffer %d \n", i);
			exit(EXIT_FAILURE);
		}
	}

	type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	if(xioctl(fd, VIDIOC_STREAMON, &type) == -1)
	{
		fprintf(stderr, "Could not turn on the streaming\n");
		exit(EXIT_FAILURE);
	}



}



