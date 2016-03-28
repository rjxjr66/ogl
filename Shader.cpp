#include "Shader.h"

#include <fstream>

#include "3DMath/Matrix.hpp"

Shader::Shader(std::string& vs, std::string& fs)
{
	GLuint ShaderObj;
	program = glCreateProgram();

	// Vertex shader
	std::ifstream ifsVS(vs);
	std::string vshader((std::istreambuf_iterator<char>(ifsVS)), std::istreambuf_iterator<char>());

	ShaderObj = glCreateShader(GL_VERTEX_SHADER);
	const char* temp_vs = vshader.c_str();
	glShaderSource(ShaderObj, 1, &temp_vs, nullptr);
	glCompileShader(ShaderObj);
	GLint success;
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];
		glGetShaderInfoLog(ShaderObj, sizeof(InfoLog), NULL, InfoLog);

		return;
	}
	glAttachShader(program, ShaderObj);

	ifsVS.close();

	// Fragment shader
	std::ifstream ifsFS(fs);
	std::string fshader((std::istreambuf_iterator<char>(ifsFS)), std::istreambuf_iterator<char>());

	ShaderObj = glCreateShader(GL_FRAGMENT_SHADER);
	const char* temp_fs = fshader.c_str();
	glShaderSource(ShaderObj, 1, &temp_fs, nullptr);
	glCompileShader(ShaderObj);
	if (!success) {
		GLchar InfoLog[1024];
		glGetShaderInfoLog(ShaderObj, sizeof(InfoLog), NULL, InfoLog);

		return;
	}
	glAttachShader(program, ShaderObj);

	ifsFS.close();

	glLinkProgram(program);


	// test
	mWorld = glGetUniformLocation(program, "gWorld");
}

void Shader::Use()
{
	glUseProgram(program);
}

