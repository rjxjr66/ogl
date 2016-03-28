#pragma once
#define PI 3.141592653589793f
#include "Vector.hpp"

template <typename T>
struct Matrix2 {
    Matrix2()
    {
        x.x = 1; x.y = 0;
        y.x = 0; y.y = 1;
    }
    Matrix2(const T* m)
    {
        x.x = m[0]; x.y = m[1];
        y.x = m[2]; y.y = m[3];
    }
    vec2 x;
    vec2 y;
};

template <typename T>
struct Matrix3 {
    Matrix3()
    {
        x.x = 1; x.y = 0; x.z = 0;
        y.x = 0; y.y = 1; y.z = 0;
        z.x = 0; z.y = 0; z.z = 1;
    }
    Matrix3(const T* m)
    {
        x.x = m[0]; x.y = m[1]; x.z = m[2];
        y.x = m[3]; y.y = m[4]; y.z = m[5];
        z.x = m[6]; z.y = m[7]; z.z = m[8];
    }
    Matrix3 Transposed() const
    {
        Matrix3 m;
        m.x.x = x.x; m.x.y = y.x; m.x.z = z.x;
        m.y.x = x.y; m.y.y = y.y; m.y.z = z.y;
        m.z.x = x.z; m.z.y = y.z; m.z.z = z.z;
        return m;
    }
    Vector3<T> operator * (const Vector3<T>& b) const
    {
        Vector3<T> v;
        v.x = x.x * b.x + x.y * b.y + x.z * b.z;
        v.y = y.x * b.x + y.y * b.y + y.z * b.z;
        v.z = z.x * b.x + z.y * b.y + z.z * b.z;
        return v;
    }
    const T* Pointer() const
    {
        return &x.x;
    }
    vec3 x;
    vec3 y;
    vec3 z;
};

template <typename T>
struct Matrix4 {
    Matrix4()
    {
        x.x = 1; x.y = 0; x.z = 0; x.w = 0;
        y.x = 0; y.y = 1; y.z = 0; y.w = 0;
        z.x = 0; z.y = 0; z.z = 1; z.w = 0;
        w.x = 0; w.y = 0; w.z = 0; w.w = 1;
    }
    Matrix4(const Matrix3<T>& m)
    {
        x.x = m.x.x; x.y = m.x.y; x.z = m.x.z; x.w = 0;
        y.x = m.y.x; y.y = m.y.y; y.z = m.y.z; y.w = 0;
        z.x = m.z.x; z.y = m.z.y; z.z = m.z.z; z.w = 0;
        w.x = 0; w.y = 0; w.z = 0; w.w = 1;
    }
    Matrix4(const T* m)
    {
        x.x = m[0];  x.y = m[1];  x.z = m[2];  x.w = m[3];
        y.x = m[4];  y.y = m[5];  y.z = m[6];  y.w = m[7];
        z.x = m[8];  z.y = m[9];  z.z = m[10]; z.w = m[11];
        w.x = m[12]; w.y = m[13]; w.z = m[14]; w.w = m[15];
    }
	Matrix4 operator + (const Matrix4& b) const {
		Matrix4 m;
		m.x = x + b.x;
		m.y = y + b.y;
		m.z = z + b.z;
		m.w = w + b.w;

		return m;
	}
    Matrix4 operator * (const Matrix4& b) const
    {
        Matrix4 m;
		m.x.x = x.x * b.x.x + y.x * b.x.y + z.x * b.x.z + w.x * b.x.w;
		m.x.y = x.y * b.x.x + y.y * b.x.y + z.y * b.x.z + w.y * b.x.w;
		m.x.z = x.z * b.x.x + y.z * b.x.y + z.z * b.x.z + w.z * b.x.w;
		m.x.w = x.w * b.x.x + y.w * b.x.y + z.w * b.x.z + w.w * b.x.w;

		m.y.x = x.x * b.y.x + y.x * b.y.y + z.x * b.y.z + w.x * b.y.w;
		m.y.y = x.y * b.y.x + y.y * b.y.y + z.y * b.y.z + w.y * b.y.w;
		m.y.z = x.z * b.y.x + y.z * b.y.y + z.z * b.y.z + w.z * b.y.w;
		m.y.w = x.w * b.y.x + y.w * b.y.y + z.w * b.y.z + w.w * b.y.w;

		m.z.x = x.x * b.z.x + y.x * b.z.y + z.x * b.z.z + w.x * b.z.w;
		m.z.y = x.y * b.z.x + y.y * b.z.y + z.y * b.z.z + w.y * b.z.w;
		m.z.z = x.z * b.z.x + y.z * b.z.y + z.z * b.z.z + w.z * b.z.w;
		m.z.w = x.w * b.z.x + y.w * b.z.y + z.w * b.z.z + w.w * b.z.w;

		m.w.x = x.x * b.w.x + y.x * b.w.y + z.x * b.w.z + w.x * b.w.w;
		m.w.y = x.y * b.w.x + y.y * b.w.y + z.y * b.w.z + w.y * b.w.w;
		m.w.z = x.z * b.w.x + y.z * b.w.y + z.z * b.w.z + w.z * b.w.w;
		m.w.w = x.w * b.w.x + y.w * b.w.y + z.w * b.w.z + w.w * b.w.w;
		
		/*
		m.x.x = x.x * b.x.x + y.x * b.x.y + z.x * b.x.z + w.x * b.x.w;
		m.x.y = x.y * b.x.x + y.y * b.x.y + z.y * b.x.z + w.y * b.x.w;
		m.x.z = x.z * b.x.x + y.z * b.x.y + z.z * b.x.z + w.z * b.x.w;
		m.x.w = x.w * b.x.x + y.w * b.x.y + z.w * b.x.z + w.w * b.x.w;
		
		m.y.x = x.x * b.y.x + y.x * b.y.y + z.x * b.y.z + w.x * b.y.w;
		m.y.y = x.y * b.y.x + y.y * b.y.y + z.y * b.y.z + w.y * b.y.w;
		m.y.z = x.z * b.y.x + y.z * b.y.y + z.z * b.y.z + w.z * b.y.w;
		m.y.w = x.w * b.y.x + y.w * b.y.y + z.w * b.y.z + w.w * b.y.w;
		
		m.z.x = x.x * b.z.x + y.x * b.z.y + z.x * b.z.z + w.x * b.z.w;
		m.z.y = x.y * b.z.x + y.y * b.z.y + z.y * b.z.z + w.y * b.z.w;
		m.z.z = x.z * b.z.x + y.z * b.z.y + z.z * b.z.z + w.z * b.z.w;
		m.z.w = x.w * b.z.x + y.w * b.z.y + z.w * b.z.z + w.w * b.z.w;
		
		m.w.x = x.x * b.w.x + y.x * b.w.y + z.x * b.w.z + w.x * b.w.w;
		m.w.y = x.y * b.w.x + y.y * b.w.y + z.y * b.w.z + w.y * b.w.w;
		m.w.z = x.z * b.w.x + y.z * b.w.y + z.z * b.w.z + w.z * b.w.w;
		m.w.w = x.w * b.w.x + y.w * b.w.y + z.w * b.w.z + w.w * b.w.w;
		*/

		return m;
    }
    Matrix4 operator * (const T b) const
    {
        Matrix4 m;
        m.x.x = x.x * b;
        m.x.y = x.y * b;
        m.x.z = x.z * b;
        m.x.w = x.w * b;
        m.y.x = y.x * b;
        m.y.y = y.y * b;
        m.y.z = y.z * b;
        m.y.w = y.w * b;
        m.z.x = z.x * b;
        m.z.y = z.y * b;
        m.z.z = z.z * b;
        m.z.w = z.w * b;
        m.w.x = w.x * b;
        m.w.y = w.y * b;
        m.w.z = w.z * b;
        m.w.w = w.w * b;
        return m;
    }
    Vector4<T> operator * (const Vector4<T>& b) const
    {
        Vector4<T> v;
        v.x = x.x * b.x + x.y * b.y + x.z * b.z + x.w * b.w;
        v.y = y.x * b.x + y.y * b.y + y.z * b.z + y.w * b.w;
        v.z = z.x * b.x + z.y * b.y + z.z * b.z + z.w * b.w;
        v.w = w.x * b.x + w.y * b.y + w.z * b.z + w.w * b.w;

		/*
		v.x = x.x * b.x + y.x * b.y + z.x * b.z + w.x * b.w;
		v.y = x.y * b.x + y.y * b.y + z.y * b.z + w.y * b.w;
		v.z = x.z * b.x + y.z * b.y + z.z * b.z + w.z * b.w;
		v.w = x.w * b.x + y.w * b.y + z.w * b.z + w.w * b.w;
		*/
        return v;
    }
    Matrix4& operator *= (const Matrix4& b)
    {
        Matrix4 m = *this * b;
        return (*this = m);
    }
    Matrix4 Transposed() const
    {
        Matrix4 m;
        m.x.x = x.x; m.x.y = y.x; m.x.z = z.x; m.x.w = w.x;
        m.y.x = x.y; m.y.y = y.y; m.y.z = z.y; m.y.w = w.y;
        m.z.x = x.z; m.z.y = y.z; m.z.z = z.z; m.z.w = w.z;
        m.w.x = x.w; m.w.y = y.w; m.w.z = z.w; m.w.w = w.w;
        return m;
    }
    /*
    ** Invert 4x4 matrix.
    ** Contributed by David Moore (See Mesa bug #6748)
    */
    Matrix4 Invert(T det)
	{
    	Matrix4 inv;
    	T* m = &x.x;

    	//inv.x.x = y.y*z.z*w.w - y.y*z.w*w.z - z.y*y.z*w.w + z.y*y.w*w.z + w.y*y.z*z.w - w.y*y.w*z.z;
    	inv.x.x =  m[5]*m[10]*m[15] - m[5]*m[11]*m[14] - m[9]*m[6]*m[15] + m[9]*m[7]*m[14] + m[13]*m[6]*m[11] - m[13]*m[7]*m[10];
    	inv.x.y = -m[1]*m[10]*m[15] + m[1]*m[11]*m[14] + m[9]*m[2]*m[15] - m[9]*m[3]*m[14] - m[13]*m[2]*m[11] + m[13]*m[3]*m[10];
    	inv.x.z =  m[1]*m[6]*m[15] - m[1]*m[7]*m[14] - m[5]*m[2]*m[15] + m[5]*m[3]*m[14] + m[13]*m[2]*m[7] - m[13]*m[3]*m[6];
    	inv.x.w = -m[1]*m[6]*m[11] + m[1]*m[7]*m[10] + m[5]*m[2]*m[11] - m[5]*m[3]*m[10] - m[9]*m[2]*m[7] + m[9]*m[3]*m[6];

    	inv.y.x = -m[4]*m[10]*m[15] + m[4]*m[11]*m[14] + m[8]*m[6]*m[15] - m[8]*m[7]*m[14] - m[12]*m[6]*m[11] + m[12]*m[7]*m[10];
    	inv.y.y =  m[0]*m[10]*m[15] - m[0]*m[11]*m[14] - m[8]*m[2]*m[15] + m[8]*m[3]*m[14] + m[12]*m[2]*m[11] - m[12]*m[3]*m[10];
    	inv.y.z = -m[0]*m[6]*m[15] + m[0]*m[7]*m[14] + m[4]*m[2]*m[15] - m[4]*m[3]*m[14] - m[12]*m[2]*m[7] + m[12]*m[3]*m[6];
    	inv.y.w =  m[0]*m[6]*m[11] - m[0]*m[7]*m[10] - m[4]*m[2]*m[11] + m[4]*m[3]*m[10] + m[8]*m[2]*m[7] - m[8]*m[3]*m[6];

    	inv.z.x =  m[4]*m[9]*m[15] - m[4]*m[11]*m[13] - m[8]*m[5]*m[15] + m[8]*m[7]*m[13] + m[12]*m[5]*m[11] - m[12]*m[7]*m[9];
    	inv.z.y = -m[0]*m[9]*m[15] + m[0]*m[11]*m[13] + m[8]*m[1]*m[15] - m[8]*m[3]*m[13] - m[12]*m[1]*m[11] + m[12]*m[3]*m[9];
    	inv.z.z =  m[0]*m[5]*m[15] - m[0]*m[7]*m[13] - m[4]*m[1]*m[15] + m[4]*m[3]*m[13] + m[12]*m[1]*m[7] - m[12]*m[3]*m[5];
    	inv.z.w = -m[0]*m[5]*m[11] + m[0]*m[7]*m[9] + m[4]*m[1]*m[11] - m[4]*m[3]*m[9] - m[8]*m[1]*m[7] + m[8]*m[3]*m[5];

    	inv.w.x = -m[4]*m[9]*m[14] + m[4]*m[10]*m[13] + m[8]*m[5]*m[14] - m[8]*m[6]*m[13] - m[12]*m[5]*m[10] + m[12]*m[6]*m[9];
    	inv.w.y = m[0]*m[9]*m[14] - m[0]*m[10]*m[13] - m[8]*m[1]*m[14] + m[8]*m[2]*m[13] + m[12]*m[1]*m[10] - m[12]*m[2]*m[9];
    	inv.w.z = -m[0]*m[5]*m[14] + m[0]*m[6]*m[13] + m[4]*m[1]*m[14] - m[4]*m[2]*m[13] - m[12]*m[1]*m[6] + m[12]*m[2]*m[5];
    	inv.w.w = m[0]*m[5]*m[10] - m[0]*m[6]*m[9] - m[4]*m[1]*m[10] + m[4]*m[2]*m[9] + m[8]*m[1]*m[6] - m[8]*m[2]*m[5];

    	det = m[0]*inv.x.x + m[1]*inv.y.x + m[2]*inv.z.x +m[3]*inv.w.x;
    	if (det == 0) {
    		return Matrix4();
    	}

    	det = 1.0f/det;

    	inv = inv * det;

    	return inv;
	}
    Matrix3<T> ToMat3() const
    {
        Matrix3<T> m;
        m.x.x = x.x; m.y.x = y.x; m.z.x = z.x;
        m.x.y = x.y; m.y.y = y.y; m.z.y = z.y;
        m.x.z = x.z; m.y.z = y.z; m.z.z = z.z;
        return m;
    }
    const T* Pointer() const
    {
        return &x.x;
    }
    static Matrix4<T> Identity()
    {
        return Matrix4();
    }
	void Decompose(Vector3<T>& vRotationAngle, Vector3<T>& vScale, Vector3<T>& vTranslate) {
		//이동
		vTranslate = Vector3<T>(w.x, w.y, w.z);
		
		//크기
		Vector3<T> scaleX(x.x, x.y, x.z);
		Vector3<T> scaleY(y.x, y.y, y.z);
		Vector3<T> scaleZ(z.x, z.y, z.z);
		vScale.x = scaleX.Length();
		vScale.y = scaleY.Length();
		vScale.z = scaleZ.Length();
		
		//회전
		float sx = z.y/vScale.z;
		float cx = sqrtf(1.0f - sx * sx);
		float xx, yy, zz;
		if (cx < 0.00001f) {
			if (sx > 0)
				xx = PI / 2;
			else
				xx = -PI / 2;

			yy = atan2f(z.x / vScale.z, x.x/vScale.x);
			zz = 0.0f;
		} else {
			xx = atan2f(sx, cx);
			yy = atan2f(-z.x / vScale.z, z.z / vScale.z);
			zz = atan2f(-x.y / vScale.x, y.y / vScale.y);
		}

		vRotationAngle = Vector3<T>(xx, yy, zz);
	}
    static Matrix4<T> Translate(T x, T y, T z)
    {
        Matrix4 m;
        m.x.x = 1; m.x.y = 0; m.x.z = 0; m.x.w = 0;
        m.y.x = 0; m.y.y = 1; m.y.z = 0; m.y.w = 0;
        m.z.x = 0; m.z.y = 0; m.z.z = 1; m.z.w = 0;
        m.w.x = x; m.w.y = y; m.w.z = z; m.w.w = 1;
        return m;
    }
    static Matrix4<T> Scale(T s)
    {
        Matrix4 m;
        m.x.x = s; m.x.y = 0; m.x.z = 0; m.x.w = 0;
        m.y.x = 0; m.y.y = s; m.y.z = 0; m.y.w = 0;
        m.z.x = 0; m.z.y = 0; m.z.z = s; m.z.w = 0;
        m.w.x = 0; m.w.y = 0; m.w.z = 0; m.w.w = 1;
        return m;
    }
    static Matrix4<T> Scale(T x, T y, T z)
    {
        Matrix4 m;
        m.x.x = x; m.x.y = 0; m.x.z = 0; m.x.w = 0;
        m.y.x = 0; m.y.y = y; m.y.z = 0; m.y.w = 0;
        m.z.x = 0; m.z.y = 0; m.z.z = z; m.z.w = 0;
        m.w.x = 0; m.w.y = 0; m.w.z = 0; m.w.w = 1;
        return m;
    }
    static Matrix4<T> RotateZ(T degrees)
    {
        T radians = degrees * 3.14159f / 180.0f;
        T s = std::sin(radians);
        T c = std::cos(radians);
        
        Matrix4 m;
        m.x.x =  c; m.x.y = -s; m.x.z = 0; m.x.w = 0;
        m.y.x =  s; m.y.y = c; m.y.z = 0; m.y.w = 0;
        m.z.x =  0; m.z.y = 0; m.z.z = 1; m.z.w = 0;
        m.w.x =  0; m.w.y = 0; m.w.z = 0; m.w.w = 1;
        return m;
    }
    static Matrix4<T> RotateY(T degrees)
    {
        T radians = degrees * 3.14159f / 180.0f;
        T s = std::sin(radians);
        T c = std::cos(radians);
        
        Matrix4 m;
        m.x.x =  c; m.x.y = 0; m.x.z = s; m.x.w = 0;
        m.y.x =  0; m.y.y = 1; m.y.z = 0; m.y.w = 0;
        m.z.x = -s; m.z.y = 0; m.z.z = c; m.z.w = 0;
        m.w.x =  0; m.w.y = 0; m.w.z = 0; m.w.w = 1;
        return m;
    }
    static Matrix4<T> RotateX(T degrees)
    {
        T radians = degrees * 3.14159f / 180.0f;
        T s = std::sin(radians);
        T c = std::cos(radians);
        
        Matrix4 m;
        m.x.x =  1; m.x.y = 0; m.x.z = 0; m.x.w = 0;
        m.y.x =  0; m.y.y = c; m.y.z =-s; m.y.w = 0;
        m.z.x =  0; m.z.y = s; m.z.z = c; m.z.w = 0;
        m.w.x =  0; m.w.y = 0; m.w.z = 0; m.w.w = 1;
        return m;
    }
    static Matrix4<T> Frustum(T tLeft, T tRight, T tBottom, T tTop, T tNear, T tFar)
    {
        T a = 2 * tNear / (tRight - tLeft);
        T b = 2 * tNear / (tTop - tBottom);
        T c = (tRight + tLeft) / (tRight - tLeft);
        T d = (tTop + tBottom) / (tTop - tBottom);
        T e = - (tFar + tNear) / (tFar - tNear);
        T f = -2 * tFar * tNear / (tFar - tNear);
        Matrix4 m;
        m.x.x = a; m.x.y = 0; m.x.z = 0; m.x.w = 0;
        m.y.x = 0; m.y.y = b; m.y.z = 0; m.y.w = 0;
        m.z.x = c; m.z.y = d; m.z.z = e; m.z.w = -1;
        m.w.x = 0; m.w.y = 0; m.w.z = f; m.w.w = 0;
        return m;
    }
	static Matrix4<T> Perspective(T fovy, T aspect, T tNear, T tFar)
	{
		Matrix4 m;
		T sine, cosine, cotangent, deltaZ;
		T radians = (T) (fovy/2.0f * Pi/180.0f);
		
		deltaZ = (T)(tFar - tNear);
		sine = (T)sin(radians);
		cosine = (T)cos(radians);
		
		if ((deltaZ == 0.0f) || (sine == 0.0f) || (aspect == 0.0f)) {
			return m;
		}
		
		cotangent = (T)(cosine / sine);
		
		m.x.x = cotangent / aspect;
		m.y.y = cotangent;
		m.z.z = -(tFar + tNear) / deltaZ;
		m.z.w = -1.0f;
		m.w.z = -2.0f * tNear * tFar / deltaZ;
		m.w.w = 0.0f;
		
		return m;
	}
	static Matrix4<T> Ortho(T xMin, T xMax, T yMin, T yMax, T zMin, T zMax)
	{
		Matrix4 m;
		
		T xDiff = xMax - xMin;
		T yDiff = yMax - yMin;
		T zDiff = zMax - zMin;

		m.x.x = 2.0f / xDiff;
		m.y.y = 2.0f / yDiff;
		m.z.z = 2.0f / zDiff;

		m.w.x = -(xMax + xMin) / xDiff;
		m.w.y = -(yMax + yMin) / yDiff;
		m.w.z = -(zMax + zMin) / zDiff;
		m.w.w = 1.0f;
		
		return m;
	}
    static Matrix4<T> LookAt(const Vector3<T>& eye,
                             const Vector3<T>& target,
                             const Vector3<T>& up)
    {
        Vector3<T> z = (eye - target).Normalized();
        Vector3<T> x = up.Cross(z).Normalized();
        Vector3<T> y = z.Cross(x).Normalized();
        
        Matrix4<T> m;
        m.x = Vector4<T>(x, 0);
        m.y = Vector4<T>(y, 0);
        m.z = Vector4<T>(z, 0);
        m.w = Vector4<T>(0, 0, 0, 1);
        
        Vector4<T> eyePrime = m * Vector4<T>(-eye, 1);
        m = m.Transposed();
        m.w = eyePrime;
        
        return m;
    }


//void gluLookAt(GLfloat eyex, GLfloat eyey, GLfloat eyez, GLfloat centerx,
//          GLfloat centery, GLfloat centerz, GLfloat upx, GLfloat upy,
//          GLfloat upz)
//{
//    GLfloat forward[3], side[3], up[3];
//    GLfloat m[4][4];
//
//    forward[0] = centerx - eyex;
//    forward[1] = centery - eyey;
//    forward[2] = centerz - eyez;
//
//    up[0] = upx;
//    up[1] = upy;
//    up[2] = upz;
//
//    normalize(forward);
//
//    /* Side = forward x up */
//    cross(forward, up, side);
//    normalize(side);
//
//    /* Recompute up as: up = side x forward */
//    cross(side, forward, up);
//
//    __gluMakeIdentityf(&m[0][0]);
//    m[0][0] = side[0];
//    m[1][0] = side[1];
//    m[2][0] = side[2];
//
//    m[0][1] = up[0];
//    m[1][1] = up[1];
//    m[2][1] = up[2];
//
//    m[0][2] = -forward[0];
//    m[1][2] = -forward[1];
//    m[2][2] = -forward[2];
//
//    glMultMatrixf(&m[0][0]);
//    glTranslatef(-eyex, -eyey, -eyez);
//}

    vec4 x;
    vec4 y;
    vec4 z;
    vec4 w;
};

typedef Matrix2<float> mat2;
typedef Matrix3<float> mat3;
typedef Matrix4<float> mat4;

