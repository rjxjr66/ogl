#pragma once
#include <GL/glew.h>
#include <GL/glut.h>

class Shader;
class Texture;
class Material {
private:
	Shader* shader;
	Texture* texture;

public:
	Material() : shader(nullptr), texture(nullptr) {};
	~Material();

	void Use();
	void SetShader(Shader* s);
	void SetTexture(Texture* t);
	Shader* GetShader() { return shader; }
};