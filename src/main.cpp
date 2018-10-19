#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLEW_STATIC
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


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
	//glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		std::cout << "Error" << std::endl;
	}

	std::cout << "OpenGL version "<< glGetString(GL_VERSION) << std::endl;

	std::cout << "GLSL version "<< glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	float positions[6] = {
		-0.5f, -0.5f,
		0.0f, 0.5f,
		0.5f, -0.5f
	};

	// Generate buffers

	unsigned int vbuffer;

	glGenBuffers(1, &vbuffer);

	glBindBuffer(GL_ARRAY_BUFFER, vbuffer);

	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void*)0);

	unsigned int shader = CreateShader();

	glUseProgram(shader);

	glDeleteShader(shader);
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