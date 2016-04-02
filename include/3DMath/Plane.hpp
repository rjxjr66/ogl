#pragma once
#include "Vector.hpp"
class Plane {
private:
	vec3 normal;
	float d;

public:
	Plane() {}

	Plane(vec3 norm, vec3 pos) {
		normal = norm.Normalized();
		d = -norm.Dot(pos);
	}

	Plane(vec3 pos1, vec3 pos2, vec3 pos3) {
		vec3 a = pos2 - pos1;
		vec3 b = pos3 - pos1;
		normal = a.Cross(b).Normalized();
		d = -normal.Dot(pos1);
	}

	Plane(vec3 norm, float dd) {
		normal = norm.Normalized();
		d=dd;
	}

	float determinant(vec3 pos) {
		float det = normal.Dot(pos) + d;
		return det;
	} //ÆÇº°½Ä
};

