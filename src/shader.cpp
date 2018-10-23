#include "shader.h"
#include <string>

#include "renderer.h"
#include <iostream>
#include <fstream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

SShader::SShader(const std::string& filename, unsigned int type)
{
	m_rendererID = CompileShader(type, parseShader(filename).str());
}
SShader::SShader(const SShader& sh)
	: m_rendererID(sh.m_rendererID) , m_Filepath(sh.m_Filepath)
{

	std::cout << "copied" << std::endl;
}
SShader::~SShader()
{
	//GLCall(glDeleteShader(m_rendererID));
}
std::stringstream SShader::parseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);
	std::string line;
	std::stringstream source;

	while (getline(stream, line))
	{
		source << line << "\n";
		//std::cout << line <<std::endl;
	}

	return source;
}

unsigned int SShader::GetUnifromLocation(const std::string& name)
{
	unsigned int location = glGetUniformLocation(m_rendererID, name.c_str());
	ASSERT(location != -1);
	return location;
}
unsigned int SShader::CompileShader( unsigned int typ, const std::string& source )
{
	unsigned int id = glCreateShader(typ);
	std::cout << "shadecompileid" << id << std::endl;
	const char* src = source.c_str();
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	std::cout << "shadecompileres" << result << std::endl;
	if (result == GL_FALSE)
	{
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		GLCall(glGetShaderInfoLog(id, length, &length, message));
		//std::cout << "Failed to compile shader" << "%d", typ << std::endl;
		std::cout << message << std::endl;
		return  0;

	}
	return id;
}

shaderProgram::shaderProgram()
{
	m_rendererID = glCreateProgram();
	std::cout << "shaderProgramID" << m_rendererID << std::endl;
}
shaderProgram::~shaderProgram()
{
	/*############################################################################

	when the SShader object is copied to vector memory the destructor destroys the
	referance ID of the compiled shader

	Hence the SShader object should be created by emblace_back while the
	optimization process afterwards

	############################################################################*/
	//glDeleteShader(m_rendererID);
}
void shaderProgram::Bind() const
{
	GLCall(glUseProgram(m_rendererID));
}
void shaderProgram::Unbind() const
{
	GLCall(glUseProgram(0));
}

void shaderProgram::AddShader(const SShader& m_SShader)
{
	shaders.push_back(m_SShader);
	std::cout <<  "pusshed shader to vec" << m_SShader.m_Filepath << std::endl;

}
unsigned int shaderProgram::GetUnifromLocation(const std::string& name)
{
	unsigned int location = glGetUniformLocation(m_rendererID, name.c_str());
	ASSERT(location != -1);
	return location;
}
void shaderProgram::DeleteShader()
{
	//GLCall(glDeleteShader(m_rendererID));

}
unsigned int shaderProgram::CreateShaderProgram()
{
	for (unsigned int i = 0; i < shaders.size(); i++)
	{
		/* code */
		std::cout << i << m_rendererID << "shaderID" << shaders[i].GetID() << std::endl;
		GLCall(glAttachShader(m_rendererID, shaders[i].GetID()));

	}

	GLCall(glLinkProgram(m_rendererID));
	GLCall(glValidateProgram(m_rendererID));

	for (unsigned int i = 0; i < shaders.size(); i++)
	{
		/* code */
		//;glDeleteShader(shaders[i].GetID());
	}

	return m_rendererID;
}
void shaderProgram::SetUniform4f(const std::string& name, float v0, float v1, float f0, float f1)
{
	GLCall(glUniform4f(GetUnifromLocation(name), v0, v1, f0, f1));
}
void shaderProgram::SetUniformMat4f(const std::string &name, glm::mat4& matrix)
{
	GLCall(glUniformMatrix4fv(GetUnifromLocation(name), 1, GL_FALSE, &matrix[0][0]));
}
