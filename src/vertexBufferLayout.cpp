#include "vertexBufferLayout.h"

vertexBufferLayout::vertexBufferLayout()
{
	m_Stride = 0;
}

vertexBufferLayout::~vertexBufferLayout()
{
	m_Stride = m_Stride;
}

template<>
void vertexBufferLayout::Push<float>(unsigned int count)
{
	m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
	m_Stride += count*vertexBufferElement::getSizeofType(GL_FLOAT);
}

template<>
void vertexBufferLayout::Push<unsigned int>(unsigned int count)
{
	m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
	m_Stride += count*vertexBufferElement::getSizeofType(GL_UNSIGNED_INT);
}

template<>
void vertexBufferLayout::Push<unsigned char>(unsigned int count)
{
	m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
	m_Stride += count*vertexBufferElement::getSizeofType(GL_UNSIGNED_BYTE);
}
