
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include "Shader.h"

float vertices[] = {
-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 0.1f,
 //0.5f, -0.5f, 0.0f,
 //0.0f,  0.5f, 0.0f,
 0.8f,  0.8f, 0.0f, 1.0f, 0.0f, 1.0f
};

unsigned int indices[] = {
	0,1,2,2,1,3
};


void processInput(GLFWwindow* window);
int main()
{


	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(800, 600, "my opengl game", NULL, NULL);
	if (window == NULL)
	{
		printf("Open Window Failed\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		printf("init glew failed");
		glfwTerminate();
		return -1;
	}
	glViewport(0, 0, 800, 600);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK); //≤ªªÊ÷∆±≥√Ê

	Shader myShader = Shader("vertexSource.txt", "fragmentSource.txt");

	unsigned int VAO;
	glGenVertexArrays(1,&VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);



	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)) );
	glEnableVertexAttribArray(1);


	//glUseProgram(shaderProgram);
	myShader.use();

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		//rendering
		glClearColor(0.4f, 0.6f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			
		//float timeValve = glfwGetTime();
		//float greenValve = (sin(timeValve) / 2.0) + 0.5;
		//int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		//
		//glUseProgram(shaderProgram);
		//glUniform4f(vertexColorLocation, 0, greenValve, 0, 1.0f);
		myShader.use();

		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();


	}
	glfwTerminate();
	return 0;
}
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}