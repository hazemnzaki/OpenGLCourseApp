#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

#include "Mesh.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "GLWindow.h"
#include "Mesh.h"
#include "Shader.h"


//Window dimensions
const GLint WIDTH = 800, HEIGHT = 600;
const float toRadians = 3.14159265f / 180.0f;

GLWindow mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

/////////////////MOVING////////////////
//bool direction = true;
//float triOffset = 0.0f;
//float triMaxOffset = 0.7f;
//float triInctrement = 0.0005f;
//
//float curAngle = 0.0f;
//
//bool sizeDirection = true;
//float curSize = 0.4f;
//float maxSize = 0.8f;
//float minSize = 0.1f;
/////////////////MOVING////////////////


// Vertex Shader
static const char* vShader = "Shaders/shader.vert";


//FGragment Shader
static const char* fShader = "Shaders/shader.frag";



void CreateObjects()
{
	/*GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f, 1.0f,  0.0f
	};*/

	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		 0.0f, -1.0f, 1.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f, 1.0f,  0.0f
	};

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj2);

}

void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

int main()
{
	mainWindow = GLWindow(800, 600);
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	GLuint uniformProjection = 0, uniformModel = 0;

	glm::mat4 projection = glm::perspective(45.0f, mainWindow.getBufferWidth() / mainWindow.getBufferHeight(),0.1f, 100.0f);

	//Loop until window closed
	while (!mainWindow.getShoulClose())
	{
		//Get + Handle user input events
		glfwPollEvents();

		/////////////////MOVING////////////////
		//if (direction)
		//{
		//	triOffset += triInctrement;
		//}
		//else
		//{
		//	triOffset -= triInctrement;
		//}

		//if (abs(triOffset) >= triMaxOffset)
		//{
		//	direction = !direction;
		//}

		//curAngle += 0.01f;
		//if (curAngle >= 360)
		//{
		//	curAngle -= 360;
		//}

		//if (sizeDirection)
		//{
		//	curSize += 0.0001f;
		//}
		//else
		//{
		//	curSize -= 0.0001f;
		//}

		//if (curSize >= maxSize || curSize <= minSize)
		//{
		//	sizeDirection = !sizeDirection;
		//}
		/////////////////MOVING////////////////


		//Clear window
		glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjctionLocation();


		glm::mat4 model;
		//model = glm::translate(model, glm::vec3(triOffset, 0.0f, -2.5f)); //MOVING
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

		meshList[0]->RenderMesh();

		model = glm::mat4();
		//model = glm::translate(model, glm::vec3(-triOffset, 1.0f , -2.5f)); //MOVING
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();


		glUseProgram(0);


		mainWindow.swapBuffers();
	}

	return 0;
}