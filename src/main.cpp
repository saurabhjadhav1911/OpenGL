#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLEW_STATIC
#define GLM_ENABLE_EXPERIMENTAL
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
#include <glm/gtx/string_cast.hpp>

inline bool exists_test0(const std::string& name) {
	std::ifstream f(name.c_str());
	return f.good();
}

float r = 0.0f, inc = 0.01f;
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  -6.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

float cameraSpeed = 1.0f;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	std::cout << xpos << " mouse pos " << ypos << std::endl;


}
glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);



void processInput(GLFWwindow *window)
{

	/*
		float cameraSpeed = 2.5f * deltaTime;
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			cameraPos += cameraSpeed * cameraFront;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			cameraPos -= cameraSpeed * cameraFront;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	*/

	glm::vec3 front;

	float yaw = r * 10.0f;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(0.0f));
	front.y = sin(glm::radians(0.0f));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(0.0f));
	cameraFront = glm::normalize(front);
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	//view = glm::mat4(1.0f);

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

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetCursorPosCallback(window, mouse_callback);

	std::cout << "OpenGL version " << glGetString(GL_VERSION) << std::endl;

	std::cout << "GLSL version " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	float positions[24] = {
		1.0f ,  -1.0f ,  -1.0f ,
		1.0f ,  -1.0f ,   1.0f ,
		-1.0f ,  -1.0f ,   1.0f ,
		-1.0f ,  -1.0f ,  -1.0f ,
		1.0f ,   1.0f ,  -1.0f ,
		1.0f ,   1.0f ,   1.0f ,
		-1.0f ,   1.0f ,   1.0f ,
		-1.0f ,   1.0f ,  -1.0f
	};

	unsigned int indices[42] = {
		1, 2, 3,
		3, 2, 1,
		3, 4, 1,
		1, 4, 3,
		5, 8, 7,
		7, 6, 5,
		1, 5, 6,
		6, 2, 1,
		2, 6, 7,
		7, 3, 2,
		3, 7, 8,
		8, 4, 3,
		5, 1, 4,
		4, 8, 5
	};
	// Generate buffers


	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	vertexArray vao;
	vertexBufferLayout layout;

	vertexBuffer vb(positions, 8 * 3 * sizeof(float));
	layout.Push<float>(3);
	vao.AddBuffer(vb, layout);

	indexBuffer ib(indices, 14);


	glm::mat4 proj = glm::ortho(-4.0f, 4.0f, -3.0f, 3.0f, -4.0f, 4.0f);


	shaderProgram shader;
	SShader vertexShader("Assets/shaders/vertexShader.glsl", GL_VERTEX_SHADER);
	SShader fragmentShader("Assets/shaders/fragmentShader.glsl", GL_FRAGMENT_SHADER);

	shader.AddShader(vertexShader);
	shader.AddShader(fragmentShader);

	glm::mat4 MVP;


	shader.CreateShaderProgram();






	shader.DeleteShader();
	Renderer rend;

	view = glm::mat4(1.0f);

	std::cout << glm::to_string(view) << std::endl;
	shader.Bind();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		/* Render here */
		rend.Clear();
		shader.Bind();

		processInput(window);

		MVP =  proj * view ;

		shader.SetUniformMat4f("u_MVP", MVP);
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