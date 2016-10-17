#ifndef H_FRAME_CONVERTER
#define H_FRAME_CONVERTER

#include "UString.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <sys/time.h>

void Clamp(uint8_t&);
void Formula(uint8_t,uint8_t,uint8_t,uint8_t&,uint8_t&,uint8_t&);


class FrameConverter
{
	FILE* m_file;
	int f_length;
	unsigned char* p_frame;
	static unsigned char* m_frame;
public:
	// Constructors and Destructors
	FrameConverter() { }
	~FrameConverter() { }

	// Getters and Setters
	unsigned char* getFrame() const { return p_frame; }

	// The Function used to convert from YUYV format to RGB format
	static void* FramePartConversion(void*);
	void StartConversion(char* file, UString& frame);
	void CreateThread(int, int, int);
	void WriteInFile();
};

struct Wrapper
{
	int m_init, m_final;
	FrameConverter* m_obj;
	Wrapper(FrameConverter* obj, int init, int final);
	//Wrapper(Wrapper&);
};

#endif