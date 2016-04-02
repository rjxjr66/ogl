#pragma once
#include "Vector.hpp"
#include "Matrix.hpp"
#include "LogPrint.h"

class Ray {
public:
	vec3 origin;
	vec3 direction;
	
public:
	Ray(vec3 _origin, vec3 _direction) : origin(_origin) ,direction(_direction) {
	}
	Ray(){};
	void Transformation(mat4 m) {
		origin = (m * vec4(origin, 1)).ToVec3();
		direction = (m * vec4(direction,0)).ToVec3();
	}
	
	bool IsIntersectionWithSphere(vec3 center, float radious) {
		float length = ((center-origin).Cross(direction)).Length() / direction.Length();
		LOG_PRINT("\nLength : %f\nOrigin : (%f, %f, %f)\nDirection : (%f, %f, %f)", length, origin.x, origin.y, origin.z, direction.x, direction.y, direction.z);
		return length <= radious;
	}

};