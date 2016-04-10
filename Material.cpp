#include "Material.h"

#include "Shader.h"

void Material::Use() {
	if (shader)
		shader->Use();
}

void Material::SetShader(Shader* s) {
	shader = s;
}