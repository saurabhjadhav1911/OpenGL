#include "renderer.h"
#include <iostream>

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum err = glGetError())
	{
		std::cout << " OpenGL error !!!!! " << err << " "  << function << " " << file << " : " << line << std::endl;
		return false;
	}
	return true;
}

Renderer::Renderer()
{

}
Renderer::~Renderer()
{

}
void Renderer::Draw(const vertexArray& va, const indexBuffer& ib , const shaderProgram& shader) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	unsigned int ibcount = ib.GetCount();
	GLCall(glDrawElements(GL_TRIANGLES, ibcount, GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}