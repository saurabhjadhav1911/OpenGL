#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLEW_STATIC
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "renderer.h"


inline bool exists_test0(const std::string& name) {
	std::ifstream f(name.c_str());
	return f.good();
}

static std::stringstream parseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);
	std::string line;
	std::stringstream source;

	while (getline(stream, line))
	{
		source << line << "\n";
	}

	return source;
}


static unsigned int CompileShader( unsigned int typ, const std::string& source )
{
	unsigned int id = glCreateShader(typ);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		//std::cout << "Failed to compile shader" << "%d", typ << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return  0;

	}
	return id;
}


static unsigned int CreateShader()
{
	//std::cout << "file exist " << exists_test0("Assets/shaders/vertexShader.glsl") << std::endl;
	const std::stringstream vertexShader = parseShader("Assets/shaders/vertexShader.glsl");
	const std::stringstream fragmentShader = parseShader("Assets/shaders/fragmentShader.glsl");

	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader.str());
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader.str());

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}


int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	//glfwInitContextVersion(3, 3);
	//glewExperimental = GL_TRUE;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		std::cout << "Error" << std::endl;
	}

	std::cout << "OpenGL version " << glGetString(GL_VERSION) << std::endl;

	std::cout << "GLSL version " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	float positions[8] = {
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.5f,  0.5f,
		-0.5f,  0.5f
	};

	unsigned int indices[6] = {
		0, 1, 2,
		2, 3, 0
	};
	// Generate buffers
	unsigned int vao;
	unsigned int vbuffer;
	unsigned int ibo;

	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);


	glGenBuffers(1, &vbuffer);

	glBindBuffer(GL_ARRAY_BUFFER, vbuffer);

	glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), positions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void*)0);

	glGenBuffers(1, &ibo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	unsigned int shader = CreateShader();



	int location = glGetUniformLocation(shader, "u_Color");
	ASSERT(location != -1);

	float r = 0.0f, inc = 0.01f;

	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteShader(shader);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader);
		GLCall(glUniform4f(location, r, 0.2f, 0.3f, 1.0f));
		glBindVertexArray(vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);


		if ((r > 1.0f) || r < 0.0f) inc = -inc;
		r += inc;
             

		GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}