#pragma once
#include <3DMath/Matrix.hpp>

class Camera {
private:
	vec3 m_eye, m_lookat, m_up;
	mat4 m_view, m_proj;

public:
	// »ý¼ºÀÚ
	Camera();
	Camera(const vec3&, const vec3&, const vec3&);

	void SetView(const vec3&, const vec3&, const vec3&);
	mat4 GetView();

	void SetProj(const mat4&);
	mat4 GetProj();

	void SetEye(const vec3&);
	void SetLookAt(const vec3&);
	void SetUp(const vec3&);
	vec3 GetEye();
	vec3 GetLookAt();
	vec3 GetUp();

	void RotateX(float);
	void RotateY(float);
	void RotateZ(float);

	void Zoom(float);
	void Pan(float downDegrees, float rightDegrees);
	void RotateView(float angle, vec3 axis);
};