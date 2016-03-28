#ifndef __SHADER_H__
#define __SHADER_H__

#include <GL/glew.h>
#include <GL/glut.h>
#include <string>

class Shader {
private:
	GLuint program;

public:
	Shader(std::string& vs, std::string& fs);

	void Use();
	GLuint mWorld;
};

#endif