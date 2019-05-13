#include "Mesh.h"

#include <vector>

#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Material.h"

Mesh::Mesh() : fvf(FVF::Position), nVertices(0), nIndeces(0), worldPosition(vec3(0)), parent(nullptr)
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
	worldPosition = v;
}

vec3* Mesh::GetPosition()
{
	return &worldPosition;
}

const mat4 Mesh::GetMatrix() {
	mat4 _mat = mat4();
	if (parent != nullptr) {
		_mat = parent->GetMatrix();
	}

	return _mat * glm::translate(mat4(), worldPosition) * world;
}

Mesh* Mesh::FromAssimpScene(const aiScene* scene) {
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	const aiMesh* paiMesh = scene->mMeshes[0];
	vertices.resize(paiMesh->mNumVertices);
	auto v = vertices.begin();
	for (unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
		const aiVector3D* pPos = &(paiMesh->mVertices[i]);
		//const aiVector3D* pNormal = &(paiMesh->mNormals[i]);
		//const aiVector3D* pTexCoord = &(paiMesh->mTextureCoords[0][i]);

		Vertex v_temp;
		v_temp.position = vec3(pPos->x, pPos->y, pPos->z);
		//v_temp.normal = vec3(pNormal->x, pNormal->y, pNormal->z);
		//v_temp.texcoord = vec2(pTexCoord->x, pTexCoord->y);

		*v++ = v_temp;
	}
	
	for (unsigned int i = 0; i < paiMesh->mNumFaces; i++) {
		const aiFace& Face = paiMesh->mFaces[i];
		indices.push_back(Face.mIndices[0]);
		indices.push_back(Face.mIndices[1]);
		indices.push_back(Face.mIndices[2]);
	}

	// Per face normal 구하기
	std::vector<Face> faces;
	for (int i = 0; i < indices.size(); i += 3) {
		Face face;
		face.a = indices[i];
		face.b = indices[i + 1];
		face.c = indices[i + 2];

		// normal = AB.cross( AC )
		vec3 a = vec3(vertices[face.a].position);
		vec3 b = vec3(vertices[face.b].position);
		vec3 c = vec3(vertices[face.c].position);
		face.normal = glm::cross((a - b), (a - c));
		face.area = glm::length(face.normal);
		face.normal = glm::normalize(face.normal);

		faces.push_back(face);
	}

	// Per vertex normal 구하기
	for (int i = 0; i < vertices.size(); i++) {
		std::vector<Face> in;
		for (int j = 0; j < faces.size(); j++) {
			if (faces[j].a == i || faces[j].b == i || faces[j].c == i) {
				in.push_back(faces[j]);
			}

			float sumOfArea = 0;
			for (int k = 0; k < in.size(); k++) {
				sumOfArea += in[k].area;
			}
			vec3 sumOfWeightedNormal = vec3();
			for (int k = 0; k < in.size(); k++) {
				sumOfWeightedNormal = sumOfWeightedNormal + (in[k].normal * (in[k].area / sumOfArea) );
			}
			vertices[i].normal = glm::normalize(sumOfWeightedNormal);
		}

		
	}

	Mesh* mesh = new Mesh();
	//mesh->fvf = FVF::Position | FVF::Normal | FVF::TexCoord;
	mesh->fvf = FVF::Position;
	mesh->nVertices = vertices.size();
	mesh->nIndeces = indices.size();

	glGenBuffers(1, &mesh->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	glGenBuffers(1, &mesh->IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// To do
	// 1. Face normal 로 line 만들어서 face_normal_mesh 만들기
	// 2. Vertex normal 로 line 만들어서 face_normal_mesh 만들기
	// 3. 1, 2의 parent 를 mesh 로 설정하기

	return mesh;
}

Mesh* Mesh::GenerateCylinder(float radius, float height, float dtheta) {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	int i = 0;

	for (float theta = 0; theta < 2 * glm::pi<float>(); theta += dtheta) {
		float x = radius * glm::cos(theta);
		float y = height / 2;
		float z = radius * glm::sin(theta);
		float x_ = radius * glm::cos(theta + dtheta);
		float y_ = height / -2;
		float z_ = radius * glm::sin(theta + dtheta);
		
		
		Vertex v[4];
		v[0].position = vec3(x, y, z);
		v[0].normal = v[0].position - vec3(0, y, 0);
		v[0].texcoord = vec2(theta / 2 * glm::pi<float>(), 0);
		v[1].position = vec3(x_, y, z_);
		v[1].normal = v[1].position - vec3(0, y, 0);
		v[1].texcoord = vec2((theta + dtheta) / 2 * glm::pi<float>(), 0);
		v[2].position = vec3(x, y_, z);
		v[2].normal = v[2].position - vec3(0, y_, 0);
		v[2].texcoord = vec2(theta / 2 * glm::pi<float>(), 1);
		v[3].position = vec3(x_, y_, z_);
		v[3].normal = v[3].position - vec3(0, y_, 0);
		v[3].texcoord = vec2((theta + dtheta) / 2 * glm::pi<float>(), 1);
		vertices.push_back(v[0]);
		vertices.push_back(v[1]);
		vertices.push_back(v[2]);
		vertices.push_back(v[3]);

		indices.push_back(i);
		indices.push_back(i+2);
		indices.push_back(i+3);
		indices.push_back(i);
		indices.push_back(i+3);
		indices.push_back(i+1);

		i += 4;
	}

	return nullptr;
}
