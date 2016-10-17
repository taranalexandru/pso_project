#include "FrameConverter.h"

unsigned char* FrameConverter::m_frame = NULL;

void* FrameConverter::FramePartConversion(void *ptr)
{
	uint8_t u,v,y1,y2,r,g,b;
	Wrapper* p = static_cast<Wrapper*>(ptr);
	
	FrameConverter* f=p->m_obj;
	unsigned char* up=f->getFrame();

	int index=p->m_init;
	if( index != 0 )
	{
		index=index/4*6;
	}
	// 4bytes YUV -> 6 bytes RGB
	for(int i=p->m_init;i < p->m_final;i+=4)
	{
		y1=up[i];
		u=up[i+1];
		y2=up[i+2];
		v=up[i+3];
		Formula(y1,u,v,r,g,b);
		
		m_frame[index++]=r;
		m_frame[index++]=g;
		m_frame[index++]=b;
		Formula(y2,u,v,r,g,b);
		
		m_frame[index++]=r;
		m_frame[index++]=g;
		m_frame[index++]=b;
	}
	return NULL;
}

void FrameConverter::CreateThread(int no, int init, int final)
{
	int iret;
	pthread_t thread;
	Wrapper wrapper(this,init,final);
	iret = pthread_create( &thread, NULL, &FrameConverter::FramePartConversion , (void*) &wrapper);
	if( iret )
	{
		fprintf(stderr, "Error pthread_create Thread%d -> error-code %d \n", no, iret);
		exit(EXIT_FAILURE);
	}
	
	iret = pthread_join(thread, NULL);

	if( iret )
	{
		fprintf(stderr, "Error pthread_join Thread%d -> error-code %d \n", no, iret);
		exit(EXIT_FAILURE);
	}

}
void FrameConverter::StartConversion(char* file, UString& frame)
{
	//struct timeval x1, x2;
	//gettimeofday(&x1,NULL);

	m_file = fopen(file,"w");
	p_frame = frame.getBuffer();
	f_length = frame.getLength()/4*6;
	m_frame = new unsigned char[f_length];

	this->CreateThread(1,0,153599);
	this->CreateThread(2,153600,307199);
	this->CreateThread(3,307200,460799);
	this->CreateThread(4,460800,614399);

	this->WriteInFile();
	fclose(m_file);
	p_frame = NULL;
	if(m_frame)
	{
		delete[] m_frame;
		m_frame = NULL;
	}

	// Checking time
	//gettimeofday(&x2,NULL);
	//float total_time=(x2.tv_sec - x1.tv_sec)*1000 + (x2.tv_usec - x1.tv_usec)/1000;
	//printf("\n %f\n",total_time);
}

void Formula(uint8_t y, uint8_t u, uint8_t v, uint8_t& r, uint8_t& g, uint8_t& b)
{
	//r = 1.164*(y-16) + 1.596*(v-128);
	//g = 1.164*(y-16) - 0.813*(v-128) - 0.391*(u-128);
	//b = 1.164*(y-16) + 2.018*(v-128);

	r = y + 1.4075 * (v - 128);
	g = y - 0.3455 * (u - 128) - 0.7169 * ( v - 128);
	b = y + 1.7790 * (u - 128);

	//r = (298*(y-16)+409*(v-128)+128) >> 8;
	//g = (298*(y-16)-100*(u-128)-208*(v-128)+128) >> 8;
	//b = (298*(y-16)+516*(u-128)) >> 8;
	
	//r = y + 1.402 * (v-128);
	//g = y - 0.344 * (u-128) - 0.714 * (v-128);
	//b = y + 1.772 * (u-128);

	Clamp(r);
	Clamp(g);
	Clamp(b);
}

void FrameConverter::WriteInFile()
{
	fwrite(m_frame, sizeof(uint8_t), f_length, m_file);
}

void Clamp(uint8_t& x)
{
	if ( x < 0 )
		x = 0;
	if ( x > 255 )
		x = 255;
}

Wrapper::Wrapper(FrameConverter* obj, int init, int final)
{
	m_init = init;
	m_final = final;
	m_obj = obj;
}

/*Wrapper::Wrapper(Wrapper& obj)
{
	m_init = obj.m_init;
	m_final = obj.m_final;
	m_obj = obj.m_obj;
}*/

