#pragma once

#include "renderer.h"
#include "vertexBuffer.h"
#include "vertexBufferLayout.h"

class vertexArray
{
public:

	vertexArray();
	~vertexArray();

	void AddBuffer(const vertexBuffer& vb, const vertexBufferLayout layout);

	void Bind() const;
	void Unbind() const;
	
private:
	unsigned int m_RendererID;
};