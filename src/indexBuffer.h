#pragma once

class indexBuffer
{
public:
	indexBuffer(const void* data, unsigned int count);
	~indexBuffer();

	void Bind() const;
	void Unbind();

private:
	unsigned int m_RendererID;
	unsigned int m_Count;

};