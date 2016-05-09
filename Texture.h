#pragma once
#include <GL/glew.h>
#include <GL/glut.h>
#include <SOIL/SOIL.h>

#include <string>

class Texture {
private:
	GLuint texture;

public:
	Texture() {};
	Texture(std::string path);

	void Load(std::string path);
	void Bind(GLenum index);
};