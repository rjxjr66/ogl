#include "Camera.h"


void Camera::SetView(const vec3& eye, const vec3& lookat, const vec3& up)
{
	m_eye = eye;
	m_lookat = lookat;
	m_up = up;

	m_view = mat4::LookAt(eye, lookat, up);
}

mat4 Camera::GetView()
{
	return m_view;
}

void Camera::SetEye(const vec3& eye)
{
	SetView(eye, m_lookat, m_up);
}

void Camera::SetLookAt(const vec3& lookat)
{
	SetView(m_eye, lookat, m_up);
}

void Camera::SetUp(const vec3& up)
{
	SetView(m_eye, m_lookat, up);
}

vec3 Camera::GetEye()
{
	return m_eye;
}

vec3 Camera::GetLookAt()
{
	return m_lookat;
}

vec3 Camera::GetUp()
{
	return m_up;
}

Camera::Camera(const vec3& eye, const vec3& lookat, const vec3& up)
{
	SetView(eye, lookat, up);
}

Camera::Camera()
{

}

void Camera::SetProj(const mat4& proj)
{
	m_proj = proj;
}

mat4 Camera::GetProj()
{
	return m_proj;
}

void Camera::RotateX(float f)
{
	vec3 newEye = (mat4::RotateX(f) * vec4(m_eye, 1)).ToVec3();

	SetView(newEye, m_lookat, m_up);
}

void Camera::RotateY(float f)
{
	vec3 newEye = (mat4::RotateY(f) * vec4(m_eye, 1)).ToVec3();

	SetView(newEye, m_lookat, m_up);
}

void Camera::RotateZ(float f)
{
	vec3 newEye = (mat4::RotateZ(f) * vec4(m_eye, 1)).ToVec3();

	SetView(newEye, m_lookat, m_up);
}

void Camera::Zoom(float f)
{
	vec3 reverseLoS = m_eye - m_lookat;

	if (f > 0) {				// If positive, zoom out.
		reverseLoS = reverseLoS * 1.1;
	}
	else if (f < 0) {		// Otherwise, zoom in
		if (reverseLoS.Length() > 0.05) { // Prevent the from point from hitting the at point.
			reverseLoS = reverseLoS * 0.9;
		}
	}

	SetView(reverseLoS + m_lookat, m_lookat, m_up);
}

void Camera::RotateView(float angle, vec3 axis)
{
	angle = angle * PI / 180;
	vec3 vNewView;

	// Get the view vector (The direction we are facing)
	vec3 vView = m_eye - m_lookat;

	// Calculate the sine and cosine of the angle once
	float cosTheta = (float)cos(angle);
	float sinTheta = (float)sin(angle);

	// Find the new x position for the new rotated point
	vNewView.x = (cosTheta + (1 - cosTheta) * axis.x * axis.x)       * vView.x;
	vNewView.x += ((1 - cosTheta) * axis.x * axis.y - axis.z * sinTheta)   * vView.y;
	vNewView.x += ((1 - cosTheta) * axis.x * axis.z + axis.y * sinTheta)   * vView.z;

	// Find the new y position for the new rotated point
	vNewView.y = ((1 - cosTheta) * axis.x * axis.y + axis.z * sinTheta)   * vView.x;
	vNewView.y += (cosTheta + (1 - cosTheta) * axis.y * axis.y)       * vView.y;
	vNewView.y += ((1 - cosTheta) * axis.y * axis.z - axis.x * sinTheta)   * vView.z;

	// Find the new z position for the new rotated point
	vNewView.z = ((1 - cosTheta) * axis.x * axis.z - axis.y * sinTheta)   * vView.x;
	vNewView.z += ((1 - cosTheta) * axis.y * axis.z + axis.x * sinTheta)   * vView.y;
	vNewView.z += (cosTheta + (1 - cosTheta) * axis.z * axis.z)       * vView.z;

	// Now we just add the newly rotated vector to our position to set
	// our new rotated view of our camera.
	vec3 newEye = m_lookat + vNewView;
	SetView(newEye, m_lookat, m_lookat.Cross(newEye));
}

void Camera::Pan(float downDegrees, float rightDegrees)
{
	// Find the vector that defines the point to move.
	vec3 reverseLoS = m_eye - m_lookat;

	// Find the orthogonal local scheme to use.
	vec3 right = m_up.Cross(reverseLoS);
	vec3 orthogUp = reverseLoS.Cross(right);

	// Rotate both vectors in question around those axes
	// we just found.
	reverseLoS = reverseLoS.RotateAxis(right, downDegrees);
	reverseLoS = reverseLoS.RotateAxis(orthogUp, rightDegrees);
	m_up = m_up.RotateAxis(right, downDegrees);
	m_up = m_up.RotateAxis(orthogUp, rightDegrees);

	// Store the vectors back into our variables. We
	// translate the reversed line of sight to return
	// it to a point. The up vector is just a vector,
	// so needs no translation.
	SetView(reverseLoS + m_lookat, m_lookat, m_up);
}

