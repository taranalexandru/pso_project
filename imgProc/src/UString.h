#ifndef H_USTRING
#define H_USTRING
#include <iostream>
#include <stdio.h>

class UString
{
private:
	unsigned char* m_buffer;
	int m_length;
public:
	// Constructors and Destructors
	UString();
	UString(unsigned char* buffer, int length);
	UString(UString&);
	~UString();

	// Setters and Getters
	int getLength() const { return m_length; }
	unsigned char* getBuffer() const { return m_buffer; }
	void setBuffer(unsigned char* buffer, int length);

	// Operators Overloading
	//UString& operator+(const UString&);
	UString& operator=(const UString& ustring);
	bool operator==(const UString& ustring);

	// Display function
	

};

#endif