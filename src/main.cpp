#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLEW_STATIC
#include <iostream>

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

static unsigned int CreateShader(const std::string& vertexShader , const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

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
	//glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		std::cout << "Error" << std::endl;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	float positions[6] = {
		-0.5f, -0.5f,
		0.0f, 0.5f,
		0.5f, -0.5f
	};

	// Generate buffers

	unsigned int buffer;

	glGenBuffers(1, &buffer);

	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void*)0);

	const std::string vertexShader =
	    "#version 330 core\n"
	    "\n"
	    "layout(location = 0) out vec4 position;\n"
	    "\n"
	    "void main()\n"
	    "{\n"
	    "	gl_Position = position;\n"

	    "}\n"
	    "/n";

	const std::string fragmentShader =
	    "#version 330 core\n"
	    "\n"
	    "layout(location = 0) in vec4 color;\n"
	    "\n"
	    "void main()\n"
	    "{\n"
	    "	color = vec4(1.0,0.0,0.0,1.0);\n"

	    "}\n"
	    "/n";

	unsigned int shader = CreateShader(vertexShader,fragmentShader);
	
	glUseProgram(shader);
	
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}