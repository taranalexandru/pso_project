#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <jpeglib.h>

#define WIDTH 640
#define HEIGHT 480
#define BYTE_PER_PIXEL 3
#define COLOR_SPACE JCS_RGB

class FrameCompresser
{
private:
	unsigned char* raw_image;
public:
	FrameCompresser(char*);
	FrameCompresser(unsigned char*);
	~FrameCompresser();
	void Compress(char* dst);
	void Decompress(char* src,char* dst);
};