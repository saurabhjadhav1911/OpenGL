#pragma once

class vertexBuffer
{
public:
	vertexBuffer(const void* data,unsigned int size);
	~vertexBuffer();

	void Bind() const;
	void Unbind() const;

private:
	unsigned int m_RendererID;
	
};