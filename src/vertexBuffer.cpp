#include <GL/glew.h>
#include "renderer.h"
#include "vertexBuffer.h"
#include <iostream>

vertexBuffer::vertexBuffer(const void* data,unsigned int size)
{
	GLCall(glGenBuffers(1, &m_RendererID));

	std::cout << "vertexBuffer created with id " << m_RendererID << std::endl;

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));

	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

vertexBuffer::~vertexBuffer()
{
	GLCall(glDeleteBuffers(1,&m_RendererID));
}

void vertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void vertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}