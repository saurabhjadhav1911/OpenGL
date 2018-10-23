#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class SShader
{

private:
	unsigned int typ;
	unsigned int m_rendererID;
	std::stringstream parseShader(const std::string& filepath);
	unsigned int CompileShader( unsigned int typ, const std::string& source );

public:
	SShader(const std::string& filename, unsigned int type);
	SShader(const SShader& sh);
	~SShader();

	std::string m_Filepath;
	unsigned int GetUnifromLocation(const std::string& name);
	void SetUniform4f(const std::string& name, float v0, float v1, float f0, float f1);
	void SetUniformMat4f(const std::string &name, glm::mat4& matrix);
	inline unsigned int GetID() {return m_rendererID; }
};

class shaderProgram
{
private:
	std::vector<SShader> shaders;
	unsigned int m_rendererID;

public:
	shaderProgram();

	~shaderProgram();
	void DeleteShader();
	void Bind() const;
	void Unbind() const;
	void AddShader(const SShader& m_SShader);
	unsigned int CreateShaderProgram();
	unsigned int GetUnifromLocation(const std::string& name);
	void SetUniform4f(const std::string& name, float v0, float v1, float f0, float f1);
	void SetUniformMat4f(const std::string &name, glm::mat4& matrix);

};