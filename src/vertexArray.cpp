#include "renderer.h"
#include <iostream>
#include "vertexArray.h"
#include "vertexBufferLayout.h"

vertexArray::vertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
	std::cout << "vertexArray created with id " << m_RendererID << std::endl;

	GLCall(glBindVertexArray(m_RendererID));
}

vertexArray::~vertexArray()
{
	GLCall(glBindVertexArray(0));
}

void vertexArray::AddBuffer(const vertexBuffer &vb, const vertexBufferLayout layout)
{
	Bind();
	vb.Bind();
	unsigned int offset = 0;
	const auto& elements = layout.getElements();
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, elements[i].count, elements[i].type, elements[i].normalised, layout.getStride() , (const void*)offset));



		std::cout << "vertex attrib ptr " << i << "  " << elements[i].count << "  " << elements[i].type << "  " << elements[i].normalised  << "  " << layout.getStride() << "  " << offset << std::endl;
		offset += (elements[i].getSizeofType(elements[i].type) * elements[i].count);
	}

}

void vertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));

}
void vertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}
