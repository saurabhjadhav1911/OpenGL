#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLEW_STATIC
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "renderer.h"
#include "vertexBuffer.h"
#include "vertexArray.h"
#include "vertexBufferLayout.h"
#include "indexBuffer.h"
#include "shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


inline bool exists_test0(const std::string& name) {
	std::ifstream f(name.c_str());
	return f.good();
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

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	vertexArray vao;
	vertexBufferLayout layout;

	vertexBuffer vb(positions, 4 * 2 * sizeof(float));
	layout.Push<float>(2);
	vao.AddBuffer(vb, layout);

	indexBuffer ib(indices, 6);


	glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);

	shaderProgram shader;
	SShader vertexShader("Assets/shaders/vertexShader.glsl", GL_VERTEX_SHADER);
	SShader fragmentShader("Assets/shaders/fragmentShader.glsl", GL_FRAGMENT_SHADER);

	shader.AddShader(vertexShader);
	shader.AddShader(fragmentShader);



	shader.CreateShaderProgram();



	float r = 0.0f, inc = 0.01f;


	shader.DeleteShader();
	Renderer rend;


	shader.Bind();
	shader.SetUniformMat4f("u_MVP", proj);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		rend.Clear();
		shader.Bind();

		shader.SetUniform4f("u_Color", r, 0.2f, 0.3f, 1.0f);


		if ((r > 1.0f) || r < 0.0f) inc = -inc;
		r += inc;


		rend.Draw(vao, ib, shader);
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}