#include "UString.h"

UString::UString()
{
	m_buffer=NULL;
	m_length=0;
}

UString::UString(unsigned char* buffer, int length)
{
	m_length=length;
	m_buffer = new unsigned char[m_length];
	for (int i=0;i < m_length;i++)
	{
		m_buffer[i]=buffer[i];
	}
}

UString::UString(UString& ustring)
{
	unsigned char* p = ustring.getBuffer();
	m_length = ustring.getLength();
	m_buffer = new unsigned char[m_length];
	for (int i=0; i < m_length; i++)
	{
		m_buffer[i]= p[i];
	}
}

UString::~UString()
{
	if ( m_buffer )
	{
		delete[] m_buffer;
		m_buffer = NULL;
	}
	m_length = 0;
}

void UString::setBuffer(unsigned char* buffer, int length)
{
	if (m_buffer)
	{
		delete[] m_buffer;
		m_buffer = NULL;
	}
	m_length = length;
	m_buffer = new unsigned char[m_length];
	for(int i=0; i < m_length; i++)
	{
		m_buffer[i]=buffer[i];
	}
}

UString& UString::operator+(const UString& ustring)
{
	int plen = ustring.getLength();
	unsigned char* p = ustring.getBuffer();
	
	if(plen == 0)
		return *this;

}


UString& UString::operator=(const UString& ustring)
{
	int plen = ustring.getLength();
	unsigned char* p = ustring.getBuffer();
	
	if(plen != m_length)
	{
		if(m_buffer)
		{
			delete[] m_buffer;
			m_buffer = NULL;
		}
		this->setBuffer(ustring.getBuffer(), plen);
		return *this;
	}
	
	this->setBuffer(ustring.getBuffer(), plen);
	return *this;
}

bool UString::operator==(const UString& ustring)
{
	int plen= ustring.getLength();
	unsigned char* p = ustring.getBuffer();
	if (plen != m_length)
	{
		return false;
	}

	for(int i =0; i < plen; i++)
	{
		if (p[i] != m_buffer[i])
			return false;
	}
	return true;
}