#include "Material.h"

#include "Shader.h"
#include "Texture.h"

void Material::Use() {
	if (shader)
		shader->Use();
	if (texture)
		texture->Bind(GL_TEXTURE0);
}

void Material::SetShader(Shader* s) {
	shader = s;
}

void Material::SetTexture(Texture* t)
{
	texture = t;
}

Material::~Material()
{
	if (shader)
		delete shader;
	if (texture)
		delete shader;
}
