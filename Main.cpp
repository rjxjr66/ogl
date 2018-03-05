#include <GL/glew.h>
#include <GL/glut.h>

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "Material.h"
#include "Camera.h"
#include "Mesh.h"
#include "Texture.h"
#include "Terrain.h"

GLuint VBO;
GLuint IBO;

Shader shader;
Camera camera;

Mesh* sphere;
Mesh* sphere2;
Material* phong;
Material* terrainMaterial;
Terrain* terrain;

using namespace glm;

void Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	static float test = 0;
	test += 0.001;

	//camera.Attach(*sphere);

	//camera.RotateY(test);

	// Box
// 	mat4 world = glm::translate(mat4(), vec3(0, 10, 0));
// 	
// 	shader.Use();
// 	glUniformMatrix4fv(shader.GetUniformVar("gWVP"), 1, GL_FALSE, &(camera.GetProj() * camera.GetView() * world)[0][0]);
// 
// 	glEnableVertexAttribArray(0);
// 
// 	glBindBuffer(GL_ARRAY_BUFFER, VBO);
// 	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
// 	
// 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
// 	
// 	glDrawElements(GL_TRIANGLES, 48, GL_UNSIGNED_INT, 0);
// 
// 	glDisableVertexAttribArray(0);

	// Sphere
	static vec3 lightDirection = vec3(-1, -1, 0);
	lightDirection = vec3(glm::rotate(mat4(1.0f), 0.01f, vec3(0, 1, 0)) * glm::rotate(mat4(1.0f), 0.01f, vec3(0, 0, 1)) * vec4(lightDirection, 0));

	sphere->GetMaterial()->Use();
	glUniformMatrix4fv(phong->GetShader()->GetUniformVar("gWorld"), 1, GL_FALSE, &sphere->GetMatrix()[0][0]);
	glUniformMatrix4fv(phong->GetShader()->GetUniformVar("gWVP"), 1, GL_FALSE, &(camera.GetProj() * camera.GetView() * sphere->GetMatrix())[0][0]);
	glUniform3fv(phong->GetShader()->GetUniformVar("gLightDirection"), 1, &lightDirection[0]);
	
	sphere->Render(0);
	
	sphere2->GetMaterial()->Use();
	glUniformMatrix4fv(phong->GetShader()->GetUniformVar("gWorld"), 1, GL_FALSE, &sphere2->GetMatrix()[0][0]);
	glUniformMatrix4fv(phong->GetShader()->GetUniformVar("gWVP"), 1, GL_FALSE, &(camera.GetProj() * camera.GetView() * sphere2->GetMatrix())[0][0]);
	glUniform3fv(phong->GetShader()->GetUniformVar("gLightDirection"), 1, &lightDirection[0]);

	sphere2->Render(0);

	terrain->GetMaterial()->Use();
	glUniformMatrix4fv(terrainMaterial->GetShader()->GetUniformVar("gWorld"), 1, GL_FALSE, &terrain->GetMatrix()[0][0]);
	glUniformMatrix4fv(terrainMaterial->GetShader()->GetUniformVar("gWVP"), 1, GL_FALSE, &(camera.GetProj() * camera.GetView() * terrain->GetMatrix())[0][0]);
	glUniform3fv(terrainMaterial->GetShader()->GetUniformVar("gLightDirection"), 1, &lightDirection[0]);

	terrain->Render(0);

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

	unsigned int indices[] = { 2, 1, 0,
								1, 2, 3,
								4, 5, 6,
								7, 6, 5,
								4, 2, 0,
								4, 6, 2,
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

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	sphere = Mesh::GenerateSphere(1, 16, 32);
	sphere->SetMaterial(phong);
	sphere->SetMatrix(glm::translate(mat4(1), vec3(0,10,0)));


	sphere2 = Mesh::GenerateSphere(1, 16, 32);
	sphere2->SetMaterial(phong);
	sphere2->SetPosition(vec3(0,10,-5));

	terrain = new Terrain("textures/pohang.png", (float)1 / (float)32);
	terrain->SetMaterial(terrainMaterial);
}

void InitShader() {
	shader.LoadShader(std::string("shaders/shader.vs"), std::string("shaders/shader.fs"));
	shader.AddUniformVar("gWVP");

	// Phong shading
	phong = new Material();
	phong->SetTexture(new Texture("textures/earthmap.jpg"));

	Shader* phongShader = new Shader(std::string("shaders/phong.vs"), std::string("shaders/phong.fs"));
	
	phongShader->AddUniformVar("gWVP");
	phongShader->AddUniformVar("gWorld");
	phongShader->AddUniformVar("gLightDirection");

	phong->SetShader(phongShader);

	terrainMaterial = new Material();
	terrainMaterial->SetTexture(new Texture("textures/height.png"));

	Shader* terrainShader = new Shader(std::string("shaders/terrain.vs"), std::string("shaders/terrain.fs"));

	terrainShader->AddUniformVar("gWVP");
	terrainShader->AddUniformVar("gWorld");
	terrainShader->AddUniformVar("gLightDirection");

	terrainMaterial->SetShader(terrainShader);
}

void Resize(int width, int height) {
	float ratio;
	if (width > height)
		ratio = (GLfloat)width / (GLfloat)height;
	else
		ratio = (GLfloat)height / (GLfloat)width;

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	camera.SetProj(glm::perspective(glm::radians(60.f), ratio, 1.f, 1000.f));
	//camera.SetProj(glm::ortho(-25.f, 25.f, -25.f, 25.f, -50.f, 50.f));
}

void Init() {
	glEnable(GL_DEPTH_TEST);

	camera.SetView(vec3(0, 60, 100), vec3(0, 0, 0), vec3(0, 1, 0));
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':
		camera.GoForward(1.0f);
		//sphere->SetPosition(vec3(0, 0, 1) + *sphere->GetPosition());
		break;
	case 's':
		camera.GoForward(-1.0f);
		//sphere->SetPosition(vec3(0, 0, -1) + *sphere->GetPosition());
		break;
	case 'a':
		//sphere->SetPosition(vec3(1, 0, 0) + *sphere->GetPosition());
		break;
	case 'd':
		//sphere->SetPosition(vec3(-1, 0, 0) + *sphere->GetPosition());
		break;
	case 'q':
		//camera.GoForward(1.0f);
		camera.TurnAround(-0.01f);
		break;
	case 'e':
		//camera.GoForward(-1.0f);
		camera.TurnAround(0.01f);
		break;
	default:
		return;
	}
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
	InitShader();
	InitGeometry();

	glutKeyboardFunc(Keyboard);
	glutDisplayFunc(Render);
	glutIdleFunc(Render);
	glutReshapeFunc(Resize);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glutMainLoop();

	return 0;
}