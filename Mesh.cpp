#include "Mesh.h"

#include <vector>

#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Material.h"

Mesh::Mesh() : fvf(FVF::Position), nVertices(0), nIndeces(0), worldPosition(vec3(0))
{

}

void Mesh::SetVertexArray(void* vertices, unsigned int size, int FVF, const std::vector<unsigned int>& indices) {
	fvf = FVF;
	nIndeces = indices.size();

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
}

Mesh* Mesh::GenerateSphere(float radius, unsigned int rings, unsigned int sectors) {
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	float const R = 1. / (float)(rings - 1);
	float const S = 1. / (float)(sectors - 1);
	int r, s;

	vertices.resize(rings * sectors);
	auto v = vertices.begin();
	for (r = 0; r < rings; r++) for (s = 0; s < sectors; s++) {
		float const y = sin(-glm::half_pi<float>() + glm::pi<float>() * r * R);
		float const x = cos(2 * glm::pi<float>() * s * S) * sin(glm::pi<float>() * r * R);
		float const z = sin(2 * glm::pi<float>() * s * S) * sin(glm::pi<float>() * r * R);

		Vertex v_temp;
		v_temp.position = vec3(x * radius, y * radius, z * radius);
		v_temp.normal = vec3(-x, -y, -z);
		v_temp.texcoord = vec2(s*S, r*R);

		*v++ = v_temp;
	}

	indices.resize(rings * sectors * 6);
	std::vector<GLuint>::iterator i = indices.begin();
	for (r = 0; r < rings - 1; r++)
		for (s = 0; s < sectors - 1; s++) {
			int curRow = r * sectors;
			int nextRow = (r + 1) * sectors;
			int nextS = (s + 1) % sectors;

			indices.push_back(nextRow + nextS);
			indices.push_back(nextRow + s);
			indices.push_back(curRow + s);

			indices.push_back(curRow + nextS);
			indices.push_back(nextRow + nextS);
			indices.push_back(curRow + s);
		}

	Mesh* mesh = new Mesh();
	mesh->fvf = FVF::Position | FVF::Normal | FVF::TexCoord;
	mesh->nVertices = vertices.size();
	mesh->nIndeces = indices.size();

	glGenBuffers(1, &mesh->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	glGenBuffers(1, &mesh->IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	return mesh;
}
 
void Mesh::Render(float dt) {
	if (material)
		material->Use();

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glEnableVertexAttribArray(0);
	if (fvf & FVF::Normal)
		glEnableVertexAttribArray(1);
	if (fvf & FVF::TexCoord)
		glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	if (fvf & FVF::Normal)
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
	if (fvf & FVF::TexCoord)
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)24);

	glDrawElements(GL_TRIANGLES, nIndeces, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void Mesh::SetPosition(const vec3& v)
{
	world[3].x = v.x;
	world[3].z = v.z;
	worldPosition = v;
}

vec3* Mesh::GetPosition()
{
	return &worldPosition;
}
