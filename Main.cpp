#include <GL/glew.h>
#include <GL/glut.h>

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "Camera.h"

GLuint VBO;
GLuint IBO;

Shader shader;
Camera camera;

using namespace glm;

void Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	static float test = 0;
	test += 0.01;

	shader.Use();

	camera.RotateY(0);
	
	mat4 world = glm::rotate(mat4(1.0f), test, vec3(0, 1, 0)) * glm::rotate(mat4(1.0f), test, vec3(0, 0, 1));

	glUniformMatrix4fv(shader.GetUniformVar("gWorld"), 1, GL_TRUE, &world[0][0]);
	glUniformMatrix4fv(shader.GetUniformVar("gView"), 1, GL_TRUE, &(camera.GetView())[0][0]);
	glUniformMatrix4fv(shader.GetUniformVar("gProj"), 1, GL_TRUE, &(camera.GetProj())[0][0]);
	glUniformMatrix4fv(shader.GetUniformVar("gWVP"), 1, GL_TRUE, &(camera.GetProj() * camera.GetView() * world)[0][0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glDrawElements(GL_TRIANGLES, 48, GL_UNSIGNED_INT, 0);


	glutSwapBuffers();
}

void InitGeometry() {
	vec3 vertices[8];
	vertices[0] = vec3(-0.5f, -0.5f, 0.5f);
	vertices[1] = vec3(0.5f, -0.5f, 0.5f);
	vertices[2] = vec3(-0.5f, 0.5f, 0.5f);
	vertices[3] = vec3(0.5f, 0.5f, 0.5f);
	vertices[4] = vec3(-0.5f, -0.5f, -0.5f);
	vertices[5] = vec3(0.5f, -0.5f, -0.5f);
	vertices[6] = vec3(-0.5f, 0.5f, -0.5f);
	vertices[7] = vec3(0.5f, 0.5f, -0.5f);

	unsigned int indices[] = { 0, 1, 2,
								1, 2, 3,
								4, 5, 6,
								5, 6, 7,
								0, 2, 4,
								2, 6, 4,
								1, 3, 5,
								3, 7, 5,
								2, 6, 7,
								2, 7, 3,
								0, 1, 4,
								4, 1, 5
							};

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void InitShader() {
	shader.LoadShader(std::string("shader.vs"), std::string("shader.fs"));
	shader.AddUniformVar("gWorld");
	shader.AddUniformVar("gView");
	shader.AddUniformVar("gProj");
	shader.AddUniformVar("gWVP");
}

void Resize(int width, int height) {
	float ratio;
	if (width > height)
		ratio = (GLfloat)width / (GLfloat)height;
	else
		ratio = (GLfloat)height / (GLfloat)width;

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	camera.SetProj(glm::perspective(glm::radians(60.f), ratio, 1.f, 1000.f));
}

void Init() {
	glEnable(GL_DEPTH_TEST);

	camera.SetView(vec3(0, 2, 4), vec3(0, 0, 0), vec3(0, 1, 0));
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

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

	Init();
	InitGeometry();
	InitShader();

	glutDisplayFunc(Render);
	glutIdleFunc(Render);
	glutReshapeFunc(Resize);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glutMainLoop();

	return 0;
}