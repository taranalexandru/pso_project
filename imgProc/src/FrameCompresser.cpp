#include "FrameCompresser.h"



FrameCompresser::FrameCompresser(char* filename)
{
	FILE* f = fopen(filename,"rb");
	if(f == NULL)
	{
		fprintf(stderr,"can't open %s\n",filename);
		exit(1);
	}
	raw_image = new unsigned char[WIDTH * HEIGHT * BYTE_PER_PIXEL];
	fread(raw_image,sizeof(unsigned char),WIDTH * HEIGHT * BYTE_PER_PIXEL,f);
	fclose(f);

}

FrameCompresser::FrameCompresser(unsigned char* image)
{
	raw_image = new unsigned char[WIDTH * HEIGHT * BYTE_PER_PIXEL];
	for(int i=0;i<WIDTH * HEIGHT * BYTE_PER_PIXEL;i++)
	{
		raw_image[i]=image[i];
	}
}

FrameCompresser::~FrameCompresser()
{
	if(raw_image)
		delete[] raw_image;
	raw_image = NULL;
}

void FrameCompresser::Compress(char* dst)
{
	// Initialiazing JPEG compression and error handling objects.
	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);
	//  Specifying the destination file.
	FILE* outfile = fopen(dst,"wb");
	if(outfile == NULL)
	{
		fprintf(stderr,"can't open %s\n",dst);
		exit(1);
	}
	jpeg_stdio_dest(&cinfo, outfile);

	// Setting the parameters.
	cinfo.image_width = WIDTH;
	cinfo.image_height = HEIGHT;
	cinfo.input_components = BYTE_PER_PIXEL;
	cinfo.in_color_space = JCS_RGB;  // COLOR_SPACE
	jpeg_set_defaults(&cinfo);

	cinfo.num_components = 3;
	cinfo.dct_method = JDCT_FLOAT;
	jpeg_set_quality(&cinfo,15,TRUE);

	// Starting the compression.
	jpeg_start_compress(&cinfo,TRUE); 

	JSAMPROW row_pointer[1];
	int row_stride = WIDTH * 3;
	while(cinfo.next_scanline < cinfo.image_height)
	{
		//printf("\nWriting...%c",raw_image[cinfo.next_scanline * row_stride]);
		row_pointer[0] = & raw_image[cinfo.next_scanline * row_stride];
		jpeg_write_scanlines(&cinfo,row_pointer,1);
	}
	// Finishing compression.
	jpeg_finish_compress(&cinfo);
	fclose(outfile);
	jpeg_destroy_compress(&cinfo);
	//printf("\n1st break");
}

void FrameCompresser::Decompress(char* src, char* dst)
{
	// Initialiazing JPEG decompression and error handling objects.
	int location = 0;
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);
	// Specifying the source file.
	FILE* infile = fopen(src,"rb");
	FILE* outfile = fopen(dst,"wb");
	if(infile == NULL)
	{
		fprintf(stderr,"can't open %s\n",src);
		exit(1);
	}
	jpeg_stdio_src(&cinfo,infile);
	// Call jpeg_read_header to obtain image informations.
	jpeg_read_header(&cinfo, TRUE);
	// Start the decompression.
	jpeg_start_decompress(&cinfo);

	if (raw_image)
		delete[] raw_image;
	raw_image = NULL;
	raw_image = new unsigned char[cinfo.output_width * cinfo.output_height * cinfo.num_components];

	JSAMPROW row_pointer[1];
	row_pointer[0] = new unsigned char[cinfo.output_width * cinfo.num_components];
	while(cinfo.output_scanline < cinfo.image_height)
	{
		jpeg_read_scanlines(&cinfo, row_pointer, 1);
		//printf("\n2nd break");
		for(int i=0; i < cinfo.image_width * cinfo.num_components; i++)
		{
			raw_image[location++] = row_pointer[0][i];
		}
	}
	// Write to File
	fwrite(raw_image,sizeof(unsigned char),cinfo.output_height*cinfo.output_width*cinfo.num_components,outfile);
	// Finish the decompression;
	jpeg_finish_decompress(&cinfo);
	delete[] row_pointer[0];
	row_pointer[0] = NULL;
	fclose(infile);
	fclose(outfile);
	jpeg_destroy_decompress(&cinfo);
	//printf("\n3rd break");
}