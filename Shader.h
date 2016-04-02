#ifndef __SHADER_H__
#define __SHADER_H__

#include <GL/glew.h>
#include <GL/glut.h>
#include <map>

#include "CHash.h"

class Shader {
private:
	GLuint program;
	std::map<CHash, GLuint> uniformVars;

public:
	Shader();
	Shader(std::string& vs, std::string& fs);

	void LoadShader(std::string& vs, std::string& fs);
	void Use();
	void AddUniformVar(const char* var);
	GLuint GetUniformVar(const char* var);
	GLuint GetUniformVar(const CHash& var);
};

#endif