#pragma once
#include <GL/glew.h>
#include <GL/glut.h>

#include <glm/glm.hpp>

using namespace glm;

class Shader;
class Mesh {
private:
	GLuint m_VBO;
	GLuint m_IBO;
	GLuint m_texture;
	mat4 m_mWorld;
	
public:
	Mesh();
};