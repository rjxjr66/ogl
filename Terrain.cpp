#include "Terrain.h"
#include <SOIL/SOIL.h>

Terrain::Terrain(std::string file, float scale)
{
	int width, height, channels;

	heightmap = SOIL_load_image(
		file.c_str(),
		&width, &height, &channels,
		SOIL_LOAD_L
	);

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	terrainMesh = new Mesh();
	for (int x = 0; x < width; x++) {
		for (int z = 0; z < height; z++) {
			Vertex v;
			v.position = vec3(x, heightmap[z*width + x] * scale, z);
			v.normal = vec3(0, 1, 0);
			v.texcoord = vec2((float)x / (float)width, (float)z / (float)height);

			vertices.push_back(v);
		}
	}

	for (int x = 0; x < width - 1; x++) {
		for (int z = 0; z < height - 1; z++) {
			int i[4];
			i[0] = z*width + x;
			i[1] = z*width + x + 1;
			i[2] = (z + 1)*width + x;
			i[3] = (z + 1)*width + x + 1;

			indices.push_back(i[0]);
			indices.push_back(i[1]);
			indices.push_back(i[2]);
			indices.push_back(i[3]);
			indices.push_back(i[2]);
			indices.push_back(i[1]);

			vertices[i[0]].normal = glm::normalize(glm::cross((vertices[i[2]].position - vertices[i[0]].position), (vertices[i[1]].position - vertices[i[0]].position)));
		}
	}

	terrainMesh->SetVertexArray(&vertices[0], vertices.size() * sizeof(Vertex), FVF::Position | FVF::Normal | FVF::TexCoord, indices);
}

Terrain::~Terrain()
{
	if (terrainMesh)
		delete terrainMesh;
}

void Terrain::Render(float dt)
{
	if (terrainMesh)
		terrainMesh->Render(dt);
}

void Terrain::SetMaterial(Material* m)
{
	if (terrainMesh)
		terrainMesh->SetMaterial(m);
}

void Terrain::SetMatrix(const mat4& m)
{
	if (terrainMesh)
		terrainMesh->SetMatrix(m);
}
