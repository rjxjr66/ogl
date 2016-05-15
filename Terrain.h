#pragma once
#include <string>
#include <glm/glm.hpp>

#include "Mesh.h"
#include "Material.h"

class Terrain {
private:
	unsigned char* heightmap;
	Mesh* terrainMesh;

public:
	Terrain(std::string file, float scale);
	~Terrain();

	void SetMaterial(Material* m);
	void SetMatrix(const mat4& m);
	const mat4& GetMatrix() { return terrainMesh->GetMatrix(); };
	Material* GetMaterial() { return terrainMesh->GetMaterial(); };

	void Update(float dt) {};
	void Render(float dt);
};