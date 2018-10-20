#pragma once

#include "renderer.h"
#include <vector>
#include <iostream>

struct vertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned int normalised;

	static unsigned int getSizeofType(unsigned int typ)
	{
		switch (typ)
		{
		case GL_FLOAT         : return sizeof(float);
		case GL_UNSIGNED_INT  : return sizeof(unsigned int);
		case GL_UNSIGNED_BYTE : return sizeof(unsigned char);

		}

		ASSERT(false);
		return 0;

	}

};

class vertexBufferLayout
{

private:
	std::vector<vertexBufferElement> m_Elements;
	unsigned int m_Stride = 0;

public:
	vertexBufferLayout();
	~vertexBufferLayout();
	inline unsigned int getStride() { return  m_Stride;}

	template<typename T>
	void Push(unsigned int count)
	{
		ASSERT(false);
	}

	inline unsigned int getStride() const { return m_Stride; }
	inline const std::vector<vertexBufferElement> getElements() const { return m_Elements; }

};