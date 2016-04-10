#pragma once
#include <GL/glew.h>
#include <GL/glut.h>

class Shader;
class Material {
private:
	Shader* shader;

public:
	Material() : shader(nullptr) {};

	void Use();
	void SetShader(Shader* s);
	Shader* GetShader() { return shader; }
};