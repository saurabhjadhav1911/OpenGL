#pragma once
#include <GL/glew.h>
#include "vertexArray.h"
#include "indexBuffer.h"
#include "shader.h"

#define ASSERT(x) if (!(x)) __builtin_trap();

#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x,__FILE__,__LINE__))


void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
	Renderer();
	~Renderer();
	void Draw(const vertexArray& va,const indexBuffer& ib ,const shaderProgram& shader) const; 
	void Clear() const;
};