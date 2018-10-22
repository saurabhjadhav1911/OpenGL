#include <GL/glew.h>
#include "renderer.h"
#include "indexBuffer.h"
#include <iostream>

indexBuffer::indexBuffer(const void* data, unsigned int count)
{
	ASSERT((sizeof(unsigned int)) == sizeof(GLuint));

	m_Count = count;
	
	GLCall(glGenBuffers(1, &m_RendererID));

	std::cout << "indexBuffer created with id " << m_RendererID << std::endl;

	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));

	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

indexBuffer::~indexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void indexBuffer::Bind()
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}
void indexBuffer::Unbind()
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}