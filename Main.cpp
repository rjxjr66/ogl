#include <GL/glew.h>
#include <GL/glut.h>

#include <iostream>

#include <3DMath/Vector.hpp>

#include "3DMath/Matrix.hpp"
#include "Shader.h"

GLuint VBO;
GLuint IBO;

Shader* shader = nullptr;

void Render() {
	glClear(GL_COLOR_BUFFER_BIT);

	shader->Use();
	glUniformMatrix4fv(shader->mWorld, 1, GL_TRUE, mat4::Identity().Pointer());

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glutSwapBuffers();
}

void InitGeometry() {
	vec3 vertices[4];
	vertices[0] = vec3(-0.5f, -0.5f, 0.0f);
	vertices[1] = vec3(0.5f, -0.5f, 0.0f);
	vertices[2] = vec3(-0.5f, 0.5f, 0.0f);
	vertices[3] = vec3(0.5f, 0.5f, 0.0f);

	unsigned int indices[] = { 0, 1, 2,
								1, 2, 3 };

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void InitShader() {
	shader = new Shader(std::string("shader.vs"), std::string("shader.fs"));
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("OpenGL");

	// glutCreateWindow 함수 뒤에 호출
	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		std::cout << "Error: " << glewGetErrorString(res) << std::endl;
		return 1;
	}

	InitGeometry();
	InitShader();

	glutDisplayFunc(Render);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glutMainLoop();

	return 0;
}