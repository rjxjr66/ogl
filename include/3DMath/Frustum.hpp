#pragma once
#include "Common.h"

#define PLANE_EPSILON 5.0f

class Frustum {
private:
	float m_fRightFactor;
	float m_fUpFactor;
	float m_fNear;
	float m_fFar;

	vec3 m_vEyePosition;
	vec3 m_vForward;
	vec3 m_vRight;
	vec3 m_vUp;

public:

	Frustum() {}

	void SetPerspective( const float fFOV, const float fViewAspect, const float fNearZ, const float fFarZ )
	{
		m_fRightFactor	=	tanf( fFOV );
		m_fUpFactor		=	m_fRightFactor * fViewAspect;
		m_fNear			=	fNearZ;
		m_fFar			=	fFarZ;
	}

	void SetFrustum ( const vec3& vEye, const vec3& vForward, const vec3& vRight, const vec3& vUp )
	{
		m_vEyePosition	=	vEye;
		m_vForward		=	vForward;
		m_vRight		=	vRight;
		m_vUp			=	vUp;
	}

	bool isInFrustum( const vec3& pos ) {
		vec3 vOP	= pos - m_vEyePosition;

 		float f = vOP.Dot(m_vForward);
// 		if( f < m_fNear || m_fFar < f )
// 			return false;

		float r	= vOP.Dot(m_vRight);
		float rLimit	=	m_fRightFactor * f;
		if(r < -rLimit || rLimit < r)
			return false;

		float u	= vOP.Dot(m_vUp);
		float	uLimit	=	m_fUpFactor * f;
		if( u < -uLimit || uLimit < u )
			return false;

		return true;
	}
};