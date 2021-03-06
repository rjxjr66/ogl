#pragma once
#include <GL/glew.h>
#include <GL/glut.h>

#include <glm/glm.hpp>
#include <vector>
#include <assimp/scene.h> 

using namespace glm;

namespace FVF {
	enum { Position = 0x0, Normal = 0x10, TexCoord = 0x100 };
}

typedef struct Vertex {
	vec3 position;
	vec3 normal;
	vec2 texcoord;
};

typedef struct Face {
	unsigned int a;
	unsigned int b;
	unsigned int c;
	vec3 normal;
	float area;
};

class Material;
class Mesh {
private:
	GLuint VBO;
	GLuint IBO;
	GLuint texture;
	mat4 world;
	vec3 worldPosition;
	Material* material;
	int fvf;

	Mesh* parent;

	int nVertices;
	int nIndeces;

	
public:
	Mesh();
	void SetVertexArray(void* vertices, unsigned int size, int FVF, const std::vector<unsigned int>& indices);
	void SetMaterial(Material* m) { material = m; };
	void SetMatrix(mat4 m) { world = m; };
	void SetPosition(const vec3& v);
	void SetParent(Mesh* p) { parent = p; };
	vec3* GetPosition();
	const mat4 GetMatrix();
	Material* GetMaterial() { return material; }
	virtual void Update(float dt) {};
	virtual void Render(float dt);
	virtual void RenderLine();

	static Mesh* GenerateSphere(float radius, unsigned int rings, unsigned int sectors);
	static Mesh* GenerateCylinder(float radius, float height, float dtheta);
	static Mesh* FromAssimpScene(const aiScene* scene);

	Mesh* perFaceNormal;
	Mesh* perVertexNormal;
};