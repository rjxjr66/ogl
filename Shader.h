#ifndef __SHADER_H__
#define __SHADER_H__

#include <GL/glew.h>
#include <GL/glut.h>
#include <map>

class Shader {
private:
	GLuint program;
	std::map<std::string, GLint> uniformVars;

public:
	Shader();
	Shader(std::string& vs, std::string& fs);

	void LoadShader(std::string& vs, std::string& fs);
	void Use();
	void AddUniformVar(const char* var);
	GLint GetUniformVar(const char* var);
};

#endif