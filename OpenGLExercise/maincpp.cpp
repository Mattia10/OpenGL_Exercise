#include <glad/glad.h>
#include <glfw3.h>
#include "Shader.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window);

//settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos; \n"
	"layout (location = 1) in vec3 aColor; //color has attribute position 1 \n "

	"out vec3 ourColor; \n"

	"void main()\n"
	"{\n"
	"	gl_Position = vec4(aPos, 1.0); \n"
	"	ourColor = aColor; \n"	
	"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor; \n"
	"in vec3 ourColor; \n"
	
	"void main()\n"
	"{\n"
	"	FragColor = vec4(ourColor, 1.0); \n"
	"}\0";

int main()
{
	// initialization and configuration
	// -----------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// -----------------------------


	//glfw window creation
	// -----------------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_WIDTH, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();

		return -1;
	}
	glfwMakeContextCurrent(window);
	//called everytime we resize the window
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// -----------------------------


	//glad: load all openGL function pointers
	// -----------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

		return -1;
	}
	// -----------------------------

	//build and compile shader program
	// -----------------------------
	Shader shader("Shaders/Shader.vs", "Shaders/Shader.fs");
	// -----------------------------


	// set up vertex data, buffers and configure vertex attribute
	// -----------------------------
	float vertices[] =
	{
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // top right
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f// bottom left
	    //-0.5f,  0.5f, 0.0f, 0.5f, 0.5f, 0.5f // top left
	};
	unsigned int indices[] =
	{
		0, 1, 2 // first triangle
		//1, 2, 3  // second triangle
	};

	unsigned int VBO, VAO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//copy the vertices array in a buffer to be used
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//unbind VAO
	glBindVertexArray(0);
	// -----------------------------


	// render loop
	// -----------------------------

	//wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!glfwWindowShouldClose(window))
	{
		//input
		ProcessInput(window);

		//rendering commands
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Use();
		//shader.setFloat("someUniform", 1.0f);
		

		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		// swap the color buffer
		// double buffer
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// deallocate resources
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// the first two param need to set the lower left corner of the window; 
	// width and height can be even smaller than glfw window size
	glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}